/*******************************************************************************
           ���ʂ����I�u�W�F�N�g�Ƃ��̏����@�\���������߂̃N���X�Q           
Copyright (C) 2012 ���\�t�g

�쐬�� ������
����� VC++ 2010 Express Edition(C++11)
�쐬���� 2012/02/27 10:37
�ŏI�X�V 2011/02/28 14:04

<�T�v>
�A�C�e���▂�@�Ȃǌ��ʂ����[�U���I����������̑ΏۂɓK������悤�ȋ@�\��񋟂���
�N���X�Q�ł��B

<�N���X�\��>
���̃N���X�Q��effect_obj�Ƃ������O��Ԃɂ܂Ƃ߂��
�������邢�̂ňȉ�����(��Œ���)�T���v������Ε�����Ǝv���B

*******************************************************************************/

#pragma warning(disable:4290)
#pragma once

#include<string>
#include<vector>
#include<stdexcept>
#include<list>
#include<memory>
#include <boost/optional.hpp>


#include "AbstructLuaObject.hpp"
#include "effect_obj_support.h"

namespace effect_obj{

//===============================EffectInterface===============================
//��flyweight�ɂ���̂�delete�̕K�v�Ȃ�
class EffectInterface{
	public:
		virtual const std::string getName() const = 0;
		virtual const std::string getType() const = 0;
		virtual lua_State* getScript() const = 0;
		virtual ~EffectInterface(){}
};



//================================EffectHandler================================
//�K���Ώۂ��Ǘ�����B
//�G�t�F�N�g�ƃ^�[�Q�b�g�Ƃ̃C���^�[�t�F�[�X�ƂȂ�B
//TargetSet�͑���Ώ�(�^�[�Q�b�g)�̏W��
template<class TargetSet>
class EffectHandler : public EffectHandlerInterface{
	public:

		//EffectHandler��Manager��append����Ƃ��ɃR���X�g���N�^�̈����Ƃ��ă^�[�Q�b�g�̏W����n��
		EffectHandler(TargetSet& TargetSet_);

		//�ȉ��̓v���O���}�͈ӎ�����K�v�͂Ȃ�
		//�^�[�Q�b�g���X�g�̎擾
		std::vector<std::string> getTargetList(std::string EffectType);
		//�^�[�Q�b�g������ł�����false��Ԃ��A�����Ă�����G�t�F�N�g���^�[�Q�b�g�ɓK��
		bool run(EffectInterface* Effect,std::string TargetName,std::string RunFunctionName);

	private:
		TargetSet& Target;
		std::vector<std::string> NULLVector;//�_�~�[�̋�̃x�N�^
};
/*TargetSet�̈Öق̃C���^�[�t�F�[�X
//����ΏۂɂȂ�^�[�Q�b�g�̌^
typedef Element
//Type����Ԃ�
std::string getType();
//�^�[�Q�b�g�ɂȂ�ꗗ��Ԃ�(�^�[�Q�b�g���Œ�̏ꍇ��"NULL"��������std::vector��Ԃ�)
std::vector<std::string> getTargetList();
//�w�肳�ꂽ���O�̃^�[�Q�b�g�̎Q�Ƃ�Ԃ�
TargetSet::Element& getElement(std::string)
//�w�肳�ꂽ���O�̃^�[�Q�b�g�������Ă��邩�ǂ�����Ԃ�
bool getAliveFlag(std::string);

*/




//================================EffectManager================================
class EffectManager{
	public:

		//�^�[�Q�b�g��I�����邽�߂̓����N���X
		class Selector;

		//�R���X�g���N�^
		//�����͎��s����Lua�̊֐���
		EffectManager(std::string RunFunctionName_):RunFunctionName(RunFunctionName_){}
		~EffectManager();

		//�G�t�F�N�g�n���h���̓o�^
		void appendHandler(EffectHandlerInterface* EffectHandler);

		//�g�p����G�t�F�N�g�I�u�W�F�N�g���󂯎��A�G�t�F�N�g�̃^�[�Q�b�g�Z���N�^��Ԃ�
		//�G�t�F�N�g�I�u�W�F�N�g�������ł��Ȃ��ꍇboost::none��Ԃ�(�܂�Ή�����G�t�F�N�g�n���h�������݂��Ȃ�)
		//�^�[�Q�b�g��I������K�v���Ȃ��ꍇ��nullptr������
		boost::optional<std::shared_ptr<Selector> > createEffectSelector(EffectInterface* Effect)throw(std::invalid_argument);


		
	private:
		//Effect�̓A�C�e���ATarget�͂��̑Ώ�
		void set(Selector* ThisSelector,EffectInterface* SetEffect,std::string TargetName);
		std::vector<EffectHandlerInterface*> EffectSpecies;
		std::string RunFunctionName;

};

//EffectManager�̓����N���X
class EffectManager::Selector{
		public:
			
			//Selector�̃C�e���[�^
			typedef std::vector<std::string>::iterator iterator;				
			iterator begin(){return TargetList.begin();}
			iterator end() {return TargetList.end();}
		
			//�G�t�F�N�g��K������^�[�Q�b�g��I�����Ĕ���
			void run(iterator Target);
			void run(std::string Target);
			void run(int Target);

			//EffectManager����Ăяo����邾���Ȃ̂Ńv���O���}�͓��Ɉӎ�����K�v�͂Ȃ�
			Selector(std::vector<std::string>& TargetList_,EffectInterface* Effect_,EffectHandlerInterface* Handler_,EffectManager* Manager_);
			//�f�X�g���N�^�͉������Ȃ�
			~Selector(){}

			//�n���h����Ԃ��A�Z���N�^������
			static EffectHandlerInterface* GetHandler(EffectManager::Selector* Self);


		private:
			std::vector<std::string> TargetList;
			EffectManager* Manager;
			EffectInterface* Effect;
			EffectHandlerInterface* Handler;
			std::string TargetName;
	};


}//effect_obj���O��ԏI���


//====================================method====================================
//EffectHandler
template<class TargetSet>
effect_obj::EffectHandler<TargetSet>::EffectHandler(TargetSet& TargetSet_):Target(TargetSet_),NULLVector(0){}

template<class TargetSet>
std::vector<std::string> effect_obj::EffectHandler<TargetSet>::getTargetList(std::string EffectType){
	if (Target.getType()==EffectType){
		return Target.getTargetList();
	}
	return NULLVector;
}

template<class TargetSet>
bool effect_obj::EffectHandler<TargetSet>::run(EffectInterface* Effect,std::string TargetName,std::string RunFunctionName){
	if (Target.getAliveFlag(TargetName) ){
		luabind::call_function<void>(Effect->getScript(),RunFunctionName.c_str(), boost::ref(Target.getElement(TargetName)));
		return true;
	}else{
		return false;
	}
}

