#ifdef MODELOBJECT_EXPORTS
#define MODELOBJECT_WRAPPER __declspec(dllexport)
#else
#define MODELOBJECT_WRAPPER __declspec(dllimport)
#endif
#pragma once

#include "feDrawableObject.h"

namespace FrogEngine 
{
	namespace Data
	{
		class feModel;
	} // namespace Data

	namespace Video
	{
		class feDriver;
	} // namespace Video

	namespace Object 
	{
		class feModelObject : public feDrawableObject
		{
		public:
			// Ctor / Dtor
			feModelObject();
			feModelObject(std::string const& name, Object::feObject* parent);
			~feModelObject();

			// Functions
		#pragma region Getters/Setters
			MODELOBJECT_WRAPPER void SetModel(Data::feModel* model);
			MODELOBJECT_WRAPPER Data::feModel* GetModel() const;
			MODELOBJECT_WRAPPER size_t GetIdxModel() const;
			MODELOBJECT_WRAPPER void SetModelIndex(size_t const& idx);
		#pragma endregion
		
			virtual void Draw(feShader* shader, unsigned int idxMesh);

		private:
			// Variables
			size_t _idxModel;

			Data::feModel* _model;
		};
	} //namespace Object
} //namespace FrogEngine