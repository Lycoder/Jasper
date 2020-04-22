#pragma once

#include <vector>

#include "runtime.hpp"
#include "error.hpp"

namespace GarbageCollector {

struct GC {
private:
	Type::Null* m_null;

public:
	std::vector<Type::Value*> m_blocks;
	std::vector<Type::Value*> m_roots;

	GC();
	
	void run ();
	void add_root (Type::Value* new_root);
	Type::Null* null();

	Type::Object* new_object ();
	Type::List* new_list ();
	Type::Integer* new_integer (int);
	Type::String* new_string (std::string);
	// TODO: Function
	Type::Error* new_error (std::string);

	// TODO: Scope
};

}
