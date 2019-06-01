#pragma once

#include "detail/common.h"

NAMESPACE_BEGIN(PYBIND11_NAMESPACE)

NAMESPACE_BEGIN(external)

template <typename... Args>
struct overload_cast_impl {
	constexpr overload_cast_impl() {} // MSVC 2015 needs this

	template <typename Return>
	constexpr auto operator()(Return(*pf)(Args...)) const noexcept
		-> decltype(pf) {
		return pf;
	}

	template <typename Return, typename Class>
	constexpr auto operator()(Return(Class::*pmf)(Args...), std::false_type = {}) const noexcept
		-> decltype(pmf) {
		return pmf;
	}

	template <typename Return, typename Class>
	constexpr auto operator()(Return(Class::*pmf)(Args...) const, std::true_type) const noexcept
		-> decltype(pmf) {
		return pmf;
	}
};

static constexpr auto const_ = std::true_type{};

NAMESPACE_END(external)

template <typename... Args>
struct overload_cast2 : external::overload_cast_impl<Args...>
{
	static external::overload_cast_impl<Args...> instance;
};

template <typename... Args>
external::overload_cast_impl<Args...> overload_cast2<Args...>::instance = {};


NAMESPACE_BEGIN(external)

template<typename Class, typename C, typename D>
void def_field(Class &c, D C::*pm, const std::string &py_var)
{
	c.def_readwrite(py_var.c_str(), pm);
}

template<typename Class, typename C, typename D>
void def_field(Class &c, const D C::*pm, const std::string &py_var)
{
	c.def_readonly(py_var.c_str(), pm);
}

template<typename Class, typename D>
void def_static_field(Class &c, D *pm, const std::string &py_var)
{
	c.def_readwrite_static(py_var.c_str(), pm);
}

template<typename Class, typename D>
void def_static_field(Class &c, const D *pm, const std::string &py_var)
{
	c.def_readonly_static(py_var.c_str(), pm);
}

NAMESPACE_END(external)


NAMESPACE_END(PYBIND11_NAMESPACE)