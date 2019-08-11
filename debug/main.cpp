#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;


int add(const char* l, const char* r)
{
	std::cout << l << r << std::endl;
	return 1;
}

int sub(int l, int r = 2)
{
	std::cout << l << r << std::endl;
	return 1;
}



PYBIND11_EMBEDDED_MODULE(hahaha, m) {
	m.def("add", &add);
	m.def("sub", &sub, "sub sub sub", py::arg("r") = 2);
}

int main()
{
	py::scoped_interpreter guard{};

	//auto m = py::module::import("hahaha");
//	py::exec(R"(
//import hahaha
//hahaha.add("222", 'helloworld')
//	)");

	py::eval_file("test.py");
}