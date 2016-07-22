#pragma once

#include "Assignment.h"
#include <unordered_map>

class LocalScope
{
public:
	LocalScope();
	~LocalScope();

	size_t numElements() const { return assignments.size() + children.size(); }
	void print(std::ostream &stream, const std::string &indent) const;
	std::vector<class AbstractNode*> instantiateChildren(const class Context *evalctx) const;
	void addChild(class ModuleInstantiation *ch);
	void apply(Context &ctx) const;

	AssignmentList assignments;
	std::vector<ModuleInstantiation*> children;
	typedef std::unordered_map<std::string, class UserFunction*> FunctionContainer;
	FunctionContainer functions;
	typedef std::unordered_map<std::string, class UserModule*> ModuleContainer;
	ModuleContainer	modules;
};
