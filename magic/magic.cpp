#include "magic.h"


magic::Magic::Magic(std::string Name_,std::string ScriptName_,std::string Explain_,int Type_):
	Name(Name_),
	ScriptName(ScriptName_),
	Explain(Explain_),
	Type(Type_){}

const std::string magic::Magic::getName(){return Name;}

magic::MagicDataBaseImplementation::Content*  magic::MagicDataBaseImplementation::getContent(const boost::property_tree::ptree::value_type& child){
	if (auto& Name_ = child.second.get_optional<std::string>("<xmlattr>.name")){
	if (const auto& Explain_ = child.second.get_optional<std::string>("Explain")){
	if (const auto& Type_ = child.second.get_optional<std::string>("Type")){
	if (const auto& ScriptName_ = child.second.get_optional<std::string>("Script")){
		return new magic::Magic(*Name_,*ScriptName_,*Explain_,basic_data::SpeciesName2ID(*Type_));
	}}}}
		
	return nullptr;
	}
const std::string magic::MagicDataBaseImplementation::getRootName(){return "MagicList";}
const std::string magic::MagicDataBaseImplementation::getFileName(){return "MagicDataBase.xml";}
