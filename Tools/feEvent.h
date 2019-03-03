#pragma once

#include <map>

#include "feDelegate.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	//Base TEmplate : DO NOT USE
	template<typename NONE>
	class feEvent {};

	template <typename R, typename... Parameters>
	class feEvent <R (Parameters...)>
	{
	public:
		//CTOR
		feEvent()
		{
			_delegates.clear();
			Logging::Logger::Instance().Log(Logging::INFORMATION, "Creating a feEvent.");
		}

		~feEvent()
		{
			Logging::Logger::Instance().Log(Logging::INFORMATION, "Deleting a feEvent.");
		}

		// Bind another free function
		template <R (*Function)(Parameters...)>
		void Bind()
		{
			void* ptr = FreeFunctionToGeneric<Function>;
			if (_delegates.count(ptr)) //check if ptr already in map
			{
				Logging::Logger::Instance().Log(Logging::INFORMATION, "Cannot Bind This Static Function Pointer, Already Binded to this Event");
				return;
			}
			
			feDelegate<R (Parameters...)> del;
			del.Bind<Function>();
			_delegates.insert(std::pair<void*, feDelegate<R(Parameters...)>>(ptr, del));
		}

		// Bind a class method
		template <class C, R(C::*Function)(Parameters...)>
		void Bind(C* instance)
		{
			void* ptr = ClassMethodToGeneric<C, Function>;
			if (_delegates.count(ptr)) //check if ptr already in map
			{
				Logging::Logger::Instance().Log(Logging::INFORMATION, "Cannot Bind This Class Member Function Pointer, Already Binded to this Event");
				return;
			}
			
			feDelegate<R (Parameters...)> del;
			del.Bind<C, Function>(instance);
			_delegates.insert(std::pair<void*, feDelegate<R(Parameters...)>>(ptr, del));
		}

		// Unbind a free function
		template <R(*Function)(Parameters...)>
		void Unbind()
		{
			void* ptr = FreeFunctionToGeneric<Function>;
			std::map<void*, feDelegate<R(Parameters...)>>::iterator it = _delegates.find(ptr);
			if (it != _delegates.end())
				_delegates.erase(it);
			else
				Logging::Logger::Instance().Log(Logging::INFORMATION, "Cannot Unbind. This func may have not been Bound before.");
		}

		// Unbind a class method
		template <class C, R(C::*Function)(Parameters...)>
		void Unbind()
		{
			void* ptr = ClassMethodToGeneric<C, Function>;
			std::map<void*, feDelegate<R(Parameters...)>>::iterator it = _delegates.find(ptr);
			if (it != _delegates.end())
				_delegates.erase(it);
			else
				Logging::Logger::Instance().Log(Logging::INFORMATION, "Cannot Unbind. This func may have not been Bound before.");
		}

		void Clear()
		{
			_delegates.clear();
		}

		// Invokes Func Binded
		void Invoke(Parameters... params) const
		{
			if (_delegates.empty())
				return;

			auto size = _delegates.size();
			auto max_size = _delegates.max_size();
			auto empty = _delegates.empty();

			std::map<void*, feDelegate<R (Parameters...)>>::const_iterator it = _delegates.begin();
			std::map<void*, feDelegate<R (Parameters...)>>::const_iterator end = _delegates.end();

			for (; it != end; it++)
			{
				(*it).second.Invoke(params...);
			}
		}

	private:
		//Cast FreefuncPtr into FunctionPtr
		template <R(*Function)(Parameters...)>
		static __forceinline void FreeFunctionToGeneric(Parameters... param1)
		{
			return (Function)(param1...);
		}

		//Cast MemberfuncPtr into FunctionPtr
		template <class C, R(C::*Function)(Parameters...)>
		static __forceinline void ClassMethodToGeneric(void* instance, Parameters... params)
		{
			return (static_cast<C*>(instance)->*Function)(params...);
		}

		//variable
		std::map<void*, feDelegate<R (Parameters...)>> _delegates;
	};

} // namespace FrogEngine