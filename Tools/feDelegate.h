#pragma once

#include <iostream>

namespace FrogEngine
{
	//Base TEmplate : DO NOT USE
	template<typename NONE>
	class feDelegate {};

	template <typename R, typename... Parameters>
	class feDelegate <R (Parameters...)>
	{
	public:
		feDelegate()
		:_bindedFunc(nullptr, nullptr)
		{
		}

		// Binds a free function
		template <void(*Function)(Parameters...)>
		void Bind()
		{
			_bindedFunc.first = nullptr;
			_bindedFunc.second = &FreeFunctionToGeneric<Function>;
		}
		
		// Binds a class method
		template <class C, void (C::*Function)(Parameters...)>
		void Bind(C* instance)
		{
			_bindedFunc.first = instance;
			_bindedFunc.second = &ClassMethodToGeneric<C, Function>;
		}

		void Unbind()
		{
			_bindedFunc.first = nullptr;
			_bindedFunc.second = nullptr;
		}

		// Invokes Func Binded
		R Invoke(Parameters... params) const
		{
			if (_bindedFunc.second == nullptr)
				return;

			return _bindedFunc.second(_bindedFunc.first, params...);
		}

		//Get Pointer to the Func Binded
		void* GetPtr()
		{
			return _bindedFunc.second;
		}

	private:
		typedef void* ClassPtr;
		typedef R(*FunctionPtr)(void*, Parameters...);
		typedef std::pair<ClassPtr, FunctionPtr> BindedFunc;

		//Cast FreefuncPtr into FunctionPtr
		template <R(*Function)(Parameters...)>
		static __forceinline void FreeFunctionToGeneric(ClassPtr, Parameters... param1)
		{
			return (Function)(param1...);
		}

		//Cast MemberfuncPtr into FunctionPtr
		template <class C, R(C::*Function)(Parameters...)>
		static __forceinline void ClassMethodToGeneric(ClassPtr instance, Parameters... params)
		{
			return (static_cast<C*>(instance)->*Function)(params...);
		}

		//variable
		BindedFunc _bindedFunc;
	};

} // namespace FrogEngine

