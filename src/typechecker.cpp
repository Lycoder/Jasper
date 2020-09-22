#include "typechecker.hpp"

#include "typed_ast.hpp"

#include <cassert>

namespace TypeChecker {

TypeChecker::TypeChecker() {
	m_core.new_builtin_type_function(-1); // 0  | function
	m_core.new_builtin_type_function(0);  // 1  | int
	m_core.new_builtin_type_function(0);  // 2  | float
	m_core.new_builtin_type_function(0);  // 3  | string
	m_core.new_builtin_type_function(1);  // 4  | array
	m_core.new_builtin_type_function(1);  // 5  | dictionary
	m_core.new_builtin_type_function(0);  // 6  | boolean
	m_core.new_builtin_type_function(0);  // 7  | unit

	m_core.new_term(1, {}, "builtin int");    // 0 | int(<>)
	m_core.new_term(2, {}, "builtin float");  // 1 | float(<>)
	m_core.new_term(3, {}, "builtin string"); // 2 | string(<>)
	m_core.new_term(6, {}, "builtin bool");   // 3 | boolean(<>)
	m_core.new_term(7, {}, "builtin unit");   // 4 | unit(<>)
}

MonoId TypeChecker::mono_int() {
	return 0;
}

MonoId TypeChecker::mono_float() {
	return 1;
}

MonoId TypeChecker::mono_string() {
	return 2;
}

MonoId TypeChecker::mono_boolean() {
	return 3;
}

MonoId TypeChecker::mono_unit() {
	return 4;
}

MonoId TypeChecker::rule_var(PolyId poly) {
	return m_core.inst_fresh(poly);
}

// Hindley-Milner [App], modified for multiple argument functions.
MonoId TypeChecker::rule_app(std::vector<MonoId> args_types, MonoId func_type) {
	MonoId return_type = m_core.new_var();
	args_types.push_back(return_type);

	MonoId deduced_func_type =
	    m_core.new_term(BuiltinType::Function, std::move(args_types));

	m_core.unify(func_type, deduced_func_type);

	return return_type;
}

} // namespace TypeChecker
