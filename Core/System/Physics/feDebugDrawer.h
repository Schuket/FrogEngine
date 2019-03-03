#pragma once

#ifdef CORE_EXPORTS
#define DEBUG_DRAWER __declspec(dllexport) 
#else
#define DEBUG_DRAWER __declspec(dllimport) 
#endif

#include <vector>

#include "btBulletDynamicsCommon.h"

#include "RHI\RHI.h"
#include "Math\Vector3d.h"

namespace FrogEngine
{
	namespace System
	{
		namespace Physics
		{

			class feDebugDrawer : public btIDebugDraw
			{
			public:
				//Functions
				feDebugDrawer();
				~feDebugDrawer();

				/* Set the mode of debug
				* debugMode : pass an enum (DebugDrawModes of Bullet lib)
				*/
				DEBUG_DRAWER virtual void setDebugMode(int debugMode);
				// Get the mode of debug
				DEBUG_DRAWER virtual int getDebugMode() const;

				virtual void Draw();

			private:
				//Struct
				struct Line
				{
					Line(Math::Vector3d from, Math::Vector3d to, Math::Vector3d color)
						:_from(from), _to(to), _color(color) {}

					Math::Vector3d _from;
					Math::Vector3d _to;
					Math::Vector3d _color;
				};

				//only here to be Overrided
				virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
				virtual void reportErrorWarning(const char* warningString);

				//no implmentation needed for those , but need to define them
				virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}
				virtual void draw3dText(const btVector3& location, const char* textString) {}

				//variable
				DebugDrawModes _debugMode = DBG_NoDebug;
				std::vector<Line> _gizmoLines;

				feShader _gizmoShader;
				feBuffer _buffer;
			};

		} //namespace Physics
	} //namespace System
} //namespace FrogEngine