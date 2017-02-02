#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <time.h>

#include "module.h"
#include "value.h"
#include "localscope.h"

class FileModule : public AbstractModule, public ASTNode
{
public:
	FileModule(const std::string &path, const std::string &filename);
	virtual ~FileModule();

	virtual AbstractNode *instantiate(const Context *ctx, const ModuleInstantiation *inst, EvalContext *evalctx = nullptr) const;
	virtual void print(std::ostream &stream, const std::string &indent) const;
	AbstractNode *instantiateWithFileContext(class FileContext *ctx, const ModuleInstantiation *inst, EvalContext *evalctx) const;

	void setModulePath(const std::string &path) { this->path = path; }
	const std::string &modulePath() const { return this->path; }
	void registerUse(const UseNode &usenode);
	void registerInclude(const std::string &localpath, const std::string &fullpath);
	bool includesChanged() const;
	bool handleDependencies();
	bool hasIncludes() const { return !this->includes.empty(); }
	bool usesLibraries() const { return !this->usedlibs.empty(); }
	bool isHandlingDependencies() const { return this->is_handling_dependencies; }

	LocalScope scope;
	typedef std::unordered_map<std::string, UseNode> ModuleContainer;
	ModuleContainer usedlibs;
private:
	struct IncludeFile {
		std::string filename;
		bool valid;
		time_t mtime;
	};

	bool include_modified(const IncludeFile &inc) const;

	typedef std::unordered_map<std::string, struct IncludeFile> IncludeContainer;
	IncludeContainer includes;
	bool is_handling_dependencies;

	std::string path;
	std::string filename;
};
