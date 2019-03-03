#include "SDKLoaderMesh.h"

#include "Material\Material.h"
#include "RHI\RHI.h"
#include "Image/Image.h"

#include "../feMeshFbx.h"

#include <cstdint>

namespace FrogEngine
{
	namespace SDK
	{
		void LoaderMesh::LoadScene(std::string const& pathDirectory, std::string const& name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius)
		{
			FbxManager* fbxManager = FbxManager::Create();

			FbxIOSettings* ioSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
			fbxManager->SetIOSettings(ioSettings);

			std::string const entireName = pathDirectory + name;

			FbxScene* scene = FbxScene::Create(fbxManager, entireName.c_str());

			FbxImporter* importer = FbxImporter::Create(fbxManager, "");
			bool status = importer->Initialize(entireName.c_str(), -1, fbxManager->GetIOSettings());
			status = importer->Import(scene);
			importer->Destroy();

			FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
			FbxAxisSystem ourAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);

			if (sceneAxisSystem != ourAxisSystem)
				ourAxisSystem.ConvertScene(scene);

			FbxSystemUnit sceneSystemUnit = scene->GetGlobalSettings().GetSystemUnit();
			if (fabs(sceneSystemUnit.GetScaleFactor() - 1.0) > 0.00001)
			{
				FbxSystemUnit ourSystemUnit(1.0);
				ourSystemUnit.ConvertScene(scene);
			}

			FbxNode* root = scene->GetRootNode();
			ProcessNode(root, nullptr, meshes, center, radius);
		}


		void LoaderMesh::ProcessNode(const FbxNode* node, const FbxNode* parent, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius)
		{
			//traiter le node courant

			const FbxNodeAttribute* att = node->GetNodeAttribute();
			if (att)
			{
				FbxNodeAttribute::EType type;
				type = att->GetAttributeType();

				switch (type)
				{
				case FbxNodeAttribute::eMesh:
					LoadMesh(node, meshes, center, radius);
					break;
				case FbxNodeAttribute::eSkeleton:
					break;
				case FbxNodeAttribute::eCamera:
					break;
				case FbxNodeAttribute::eLight:
					break;
				default:
					break;
				}
			}

			int childCount = node->GetChildCount();

			for (int i = 0; i < childCount; ++i)
			{
				const FbxNode* child = node->GetChild(i);
				ProcessNode(child, node, meshes, center, radius);
			}
		}

		void LoaderMesh::LoadMesh(const FbxNode* node, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius)
		{
			Math::Vector3d limitPlus;
			Math::Vector3d limitMinus;

			feMaterialFbx* meshMtl = new feMaterialFbx();

			FbxNode* mutable_node = const_cast<FbxNode*>(node);
			FbxMesh* mesh = mutable_node->GetMesh();

			// determine si la presence de tangente
			FbxLayerElementTangent* meshTan = mesh->GetElementTangent(0);
			if (!meshTan)
			{
				mesh->GenerateTangentsDataForAllUVSets(true);
				meshTan = mesh->GetElementTangent(0);
			}

			FbxLayerElement::EMappingMode tanMode = meshTan->GetMappingMode();
			FbxLayerElement::EReferenceMode tanRefMode = meshTan->GetReferenceMode();

			auto materialCount = mesh->GetElementMaterialCount();
			FbxSurfaceMaterial* mtl = nullptr;
			FbxLayerElementMaterial* mtlLayerElement = mesh->GetElementMaterial(0);
			if (mtlLayerElement->GetMappingMode() == FbxLayerElement::eAllSame)
			{
				int index = mtlLayerElement->GetIndexArray()[0];
				mtl = node->GetMaterial(0);
			}
			else
			{
			}
			
			FbxString type = mtl->ShadingModel.Get();
			const FbxProperty propertyDiffuse = mtl->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (propertyDiffuse.IsValid())
			{
				const FbxProperty factorDiffuse = mtl->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
				FbxDouble3 color = propertyDiffuse.Get<FbxDouble3>();
				if (factorDiffuse.IsValid())
				{
					double factor = factorDiffuse.Get<double>();
					color[0] *= factor;
					color[1] *= factor;
					color[2] *= factor;
				}

				int texCount = propertyDiffuse.GetSrcObjectCount<FbxFileTexture>();
				FbxFileTexture* tex = propertyDiffuse.GetSrcObject<FbxFileTexture>(0);
				if (tex)
				{
					const char* filename = tex->GetFileName();
					meshMtl->_texDiffuse.Load(filename, TypeTexture::TEXTURE_2D, TypeTexture::TEXTURE_2D);
					meshMtl->_hasDiffuse = true;
				}
				meshMtl->_kd.X((const float)(color[0]));
				meshMtl->_kd.Y((const float)(color[1]));
				meshMtl->_kd.Z((const float)(color[2]));
			}

			const FbxProperty propertySpecular = mtl->FindProperty(FbxSurfaceMaterial::sSpecular);
			if (propertySpecular.IsValid())
			{
				const FbxProperty factorSpecular = mtl->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
				FbxDouble3 color = propertySpecular.Get<FbxDouble3>();
				if (factorSpecular.IsValid())
				{
					double factor = factorSpecular.Get<double>();
					color[0] *= factor;
					color[1] *= factor;
					color[2] *= factor;
				}

				int texCount = propertySpecular.GetSrcObjectCount<FbxFileTexture>();
				FbxFileTexture* tex = propertySpecular.GetSrcObject<FbxFileTexture>(0);
				if (tex)
				{
					const char* filename = tex->GetFileName();
					meshMtl->_texSpecular.Load(filename, TypeTexture::TEXTURE_2D, TypeTexture::TEXTURE_2D);
					meshMtl->_hasSpecular = true;
				}
				meshMtl->_ks.X((const float)(color[0]));
				meshMtl->_ks.X((const float)(color[1]));
				meshMtl->_ks.X((const float)(color[2]));
			}

			const FbxProperty propertyBump = mtl->FindProperty(FbxSurfaceMaterial::sBump);
			if (propertyBump.IsValid())
			{
				const FbxProperty factorBump = mtl->FindProperty(FbxSurfaceMaterial::sBumpFactor);
				if (factorBump.IsValid())
					double factor = factorBump.Get<double>();

				int texCount = propertyBump.GetSrcObjectCount<FbxFileTexture>();
				FbxFileTexture* tex = propertyBump.GetSrcObject<FbxFileTexture>(0);
				if (tex)
				{
					const char* filename = tex->GetFileName();
					meshMtl->_texNormal.Load(filename, TypeTexture::TEXTURE_2D, TypeTexture::TEXTURE_2D);
					meshMtl->_hasNormal = true;
				}
			}
			
			FbxAMatrix globalTransform = node->GetScene()->GetAnimationEvaluator()->GetNodeGlobalTransform(mutable_node);

			FbxVector4 translation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
			FbxVector4 rotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
			FbxVector4 scale = node->GetGeometricScaling(FbxNode::eSourcePivot);
			FbxAMatrix geometryTransform;
			geometryTransform.SetTRS(translation, rotation, scale);

			FbxAMatrix finalGlobalTransform = globalTransform * geometryTransform;

			//auto vertexCount = mesh->GetControlPointsCount();

			feVertices vertices;
			//std::vector<float> vertices;

			// lecture des indices
			//auto indexCount = mesh->GetPolygonVertexCount();
			//std::vector<uint16_t> indices;

			// recupere la liste des canaux UV
			FbxStringList UVChannelNames;
			mesh->GetUVSetNames(UVChannelNames);
			auto UVChannelCount = UVChannelNames.GetCount();

			auto polyCount = mesh->GetPolygonCount();
			// met 1 - duplication des attributs
			vertices._indices.reserve(polyCount * 3);

			for (auto poly = 0; poly < polyCount; poly++)
			{
				//faces
				for (auto i = 0; i < 3; i++)
				{
					//elements
					auto index = mesh->GetPolygonVertex(poly, i);

					// met 1 - duplication des attributs
					vertices._indices.emplace_back((uint16_t)(poly * 3 + i));

					//attributs
					FbxVector4 point = mesh->GetControlPointAt(index);
					point = finalGlobalTransform.MultT(point);
					vertices.SetPositions(Math::Vector3d((float)point.mData[0], (float)point.mData[1], (float)point.mData[2]));

					CheckLimit(Math::Vector3d((float)point.mData[0], (float)point.mData[1], (float)point.mData[2]), limitPlus, limitMinus);

					//normal(x,y,z)
					FbxVector4 normal;
					mesh->GetPolygonVertexNormal(poly, i, normal);
					normal = finalGlobalTransform.MultT(normal);
					vertices.SetNormals(Math::Vector3d((float)normal.mData[0], (float)normal.mData[1], (float)normal.mData[2]));

					//texcoord(u,v)
					auto uv_channel = UVChannelNames.GetStringAt(0);
					FbxVector2 texcoords;
					bool isUnMapped = false;
					bool hasUV = mesh->GetPolygonVertexUV(poly, i, uv_channel, texcoords, isUnMapped);
					vertices.SetTexCoords(Math::Vector2d((float)texcoords.mData[0], (float)texcoords.mData[1]));

					FbxVector4 tangent;
					if (tanRefMode == FbxLayerElement::eDirect)
					{
						tangent = meshTan->GetDirectArray().GetAt(index);
					}
					else //if (tanRefMode == FbxLayerElement::eIndexToDirect)
					{
						int inDirectIndex = meshTan->GetIndexArray().GetAt(index);
						tangent = meshTan->GetDirectArray().GetAt(inDirectIndex);
					}
					vertices.SetTangent(Math::Vector3d((float)tangent.mData[0], (float)tangent.mData[1], (float)tangent.mData[2]));
				}
			}
			
			center.X((limitPlus.X() + limitMinus.X()) / 2.f);
			center.Y((limitPlus.Y() + limitMinus.Y()) / 2.f);
			center.Z((limitPlus.Z() + limitMinus.Z()) / 2.f);

			limitPlus.X((limitPlus.X() - limitMinus.X()) / 2.f);
			limitPlus.Y((limitPlus.Y() - limitMinus.Y()) / 2.f);
			limitPlus.Z((limitPlus.Z() - limitMinus.Z()) / 2.f);

			radius = limitPlus.X();
			radius = limitPlus.Y() >= limitPlus.X() && limitPlus.Y() >= limitPlus.Z() ? limitPlus.Y() : radius;
			radius = limitPlus.Z() >= limitPlus.X() && limitPlus.Z() >= limitPlus.Y() ? limitPlus.Z() : radius;

			meshes.push_back(new Mesh::feMeshFbx("", vertices, meshMtl));
		}

		void LoaderMesh::CheckLimit(Math::Vector3d vertex, Math::Vector3d& limitPlus, Math::Vector3d& limitMinus)
		{
			if (vertex.X() > limitPlus.X())
				limitPlus.X(vertex.X());
			else if (vertex.X() < limitMinus.X())
				limitMinus.X(vertex.X());

			if (vertex.Y() > limitPlus.Y())
				limitPlus.Y(vertex.Y());
			else if (vertex.Y() < limitMinus.Y())
				limitMinus.Y(vertex.Y());

			if (vertex.Z() > limitPlus.Z())
				limitPlus.Z(vertex.Z());
			else if (vertex.Z() < limitMinus.Z())
				limitMinus.Z(vertex.Z());
		}
	}
}