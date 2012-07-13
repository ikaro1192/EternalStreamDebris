#include "item.h"

//=================================Item Methods=================================

item::Item::Item(
	const std::shared_ptr<effect_obj::EffectInterface>& Effect_,
	const std::string& Name_,
	const std::string& Explain_,
	const unsigned int Price_
	):
	Effect(Effect_),
	Name(Name_),
	Explain(Explain_),
	Price(Price_)
	{}

std::shared_ptr<effect_obj::EffectInterface> item::Item::getEffect() const{return Effect;}

const std::string item::Item::getName() const{return Name;}

const std::string item::Item::getExplain() const{return Explain;}

const unsigned int item::Item::getPrice() const{return Price;}




//==============================HavingItem Methods==============================



item::HavingItem::HavingItem(const std::string& ItemName):
bag::AbstructHavingObject<std::shared_ptr<Item>,9,HavingItem>(item::ItemDataBase::get(ItemName))//å¬ÅXèCê≥ÇµÇΩ
	{}

std::shared_ptr<effect_obj::EffectInterface> item::HavingItem::getEffect() const{return Self->getEffect();}

const std::string item::HavingItem::getName() const{return Self->getName();}

const std::string item::HavingItem::getExplain() const{return Self->getExplain();}

const unsigned int item::HavingItem::getPrice() const{return Self->getPrice();}
