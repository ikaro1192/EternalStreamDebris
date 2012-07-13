#pragma once
#pragma warning(disable:4290)

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


#include "effect_obj.h"
#include "container_database.hpp"
#include "bag.hpp"


namespace item{

//=====================================Item=====================================
class Item{
	public:

		//コンストラクタ;
		Item(const std::shared_ptr<effect_obj::EffectInterface>& Effect_, const std::string& Name_, const std::string& Explain_, const unsigned int Price_);

		std::shared_ptr<effect_obj::EffectInterface> getEffect()const;
		const std::string getName() const ;
		const std::string getExplain() const;
		const unsigned int getPrice() const;

	private:
		std::shared_ptr<effect_obj::EffectInterface> Effect;
		const std::string Name;
		const std::string Explain;
		const unsigned int Price;
};

//==========================ItemDataBaseImplementation==========================
class ItemDataBaseImplementation{
public:
	typedef Item Content;
	static  Content* getContent(const boost::property_tree::ptree::value_type& child){
		if (auto& Name = child.second.get_optional<std::string>("<xmlattr>.name")){
		if (const auto& Script_ = child.second.get_optional<std::string>("Script")){
		if (const auto& Explain_ = child.second.get_optional<std::string>("Explain")){
		if (const auto& Price_ = child.second.get_optional<int>("Price")){
		if (const auto& Type_ = child.second.get_optional<std::string>("TargetType")){
			return new Item(std::shared_ptr<effect_obj::EffectInterface>(new effect_obj::Effect(Name.get(),Type_.get(),Script_.get())),Name.get(),Explain_.get(),Price_.get());
		}}}}}
		return nullptr;
	}
	
	static const std::string getRootName(){return "ItemList";}
	static const std::string getFileName(){return "ItemDataBase.xml";}

};

typedef content_data_base::ContentDataBase<item::ItemDataBaseImplementation> ItemDataBase;

//==================================HavingItem==================================
class HavingItem:public bag::AbstructHavingObject<std::shared_ptr<Item>,9,HavingItem>{
	public:

		HavingItem(const std::string& ItemName);

		std::shared_ptr<effect_obj::EffectInterface> getEffect() const;
		const std::string getName() const;
		const std::string getExplain() const;
		const unsigned int getPrice() const;

};

typedef bag::ContentBag<item::HavingItem> ItemBag;

}//名前空間終わり




