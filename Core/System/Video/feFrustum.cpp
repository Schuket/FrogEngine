#include "feFrustum.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace System
	{
		namespace Video
		{
			feFrustum::feFrustum()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feFrustum is creating. . .");
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feFrustum created !");
			}

			feFrustum::feFrustum(feFrustum const& copy)
			{
				_planes = copy._planes;
				_depth = copy._depth;
			}

			feFrustum::~feFrustum()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feFrustum is deleting. . .");
				_planes.clear();
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feFrustum deleted !");
			}

			feFrustum* feFrustum::Clone()
			{
				return new feFrustum(*this);
			}

#pragma region Getter / Setter
			void feFrustum::SetDepth(float const& depth)
			{
				_depth = depth;
			}

			float feFrustum::GetDepth() const
			{
				return _depth;
			}
#pragma endregion

			void feFrustum::ConstructPlanes(Math::Matrix4 proj, Math::Matrix4 view)
			{
				_planes.clear();

				Math::Matrix4 matrix;
				matrix = proj * view;

				///////////// Near
				Math::Vector4d plane;
				plane.X(matrix.DataArray()[3] + matrix.DataArray()[2]);
				plane.Y(matrix.DataArray()[7] + matrix.DataArray()[6]);
				plane.Z(matrix.DataArray()[11] + matrix.DataArray()[10]);
				plane.W(matrix.DataArray()[15] + matrix.DataArray()[14]);
				
				_planes.push_back(plane);

				///////////// Far
				plane.X(matrix.DataArray()[3] - matrix.DataArray()[2]);
				plane.Y(matrix.DataArray()[7] - matrix.DataArray()[6]);
				plane.Z(matrix.DataArray()[11] - matrix.DataArray()[10]);
				plane.W(matrix.DataArray()[15] - matrix.DataArray()[14]);

				_planes.push_back(plane);

				///////////// Left
				plane.X(matrix.DataArray()[3] + matrix.DataArray()[0]);
				plane.Y(matrix.DataArray()[7] + matrix.DataArray()[4]);
				plane.Z(matrix.DataArray()[11] + matrix.DataArray()[8]);
				plane.W(matrix.DataArray()[15] + matrix.DataArray()[12]);

				_planes.push_back(plane);

				//////////// Right
				plane.X(matrix.DataArray()[3] - matrix.DataArray()[0]);
				plane.Y(matrix.DataArray()[7] - matrix.DataArray()[4]);
				plane.Z(matrix.DataArray()[11] - matrix.DataArray()[8]);
				plane.W(matrix.DataArray()[15] - matrix.DataArray()[12]);

				_planes.push_back(plane);

				//////////// Top
				plane.X(matrix.DataArray()[3] - matrix.DataArray()[1]);
				plane.Y(matrix.DataArray()[7] - matrix.DataArray()[5]);
				plane.Z(matrix.DataArray()[11] - matrix.DataArray()[9]);
				plane.W(matrix.DataArray()[15] - matrix.DataArray()[13]);

				_planes.push_back(plane);

				/////////// Bottom
				plane.X(matrix.DataArray()[3] + matrix.DataArray()[1]);
				plane.Y(matrix.DataArray()[7] + matrix.DataArray()[5]);
				plane.Z(matrix.DataArray()[11] + matrix.DataArray()[9]);
				plane.W(matrix.DataArray()[15] + matrix.DataArray()[13]);

				_planes.push_back(plane);

				size_t size = _planes.size();
				for (int idx = 0; idx < size; ++idx)
				{
					Math::Vector3d vec3(_planes[idx].X(), _planes[idx].Y(), _planes[idx].Z());
					float norm = vec3.Norm();
					_planes[idx] = Math::Vector4d(_planes[idx].X()/ norm, _planes[idx].Y() / norm, _planes[idx].Z() / norm, _planes[idx].W() / norm);
				}
			}

			bool feFrustum::CheckSphere(Math::Vector3d center, float radius)
			{
				size_t size = _planes.size();
				for (int i = 0; i < size; ++i)
				{
					if (_planes[i].Dot(Math::Vector4d(center, 1.f)) < -radius)
						return false;
				}

				return true;
			}
		} // namespace Video
	} // namespace System
} // namespace FrogEngine