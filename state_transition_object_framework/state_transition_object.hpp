

/*******************************************************************************
            ��ԑJ�ڂ���(����)�I�u�W�F�N�g���������߂̃t���[�����[�N

Copyright (C) 2012 ���\�t�g


�쐬��  ������
����� VC++ 2010 Express Edition
�쐬���� 2011/08/21 10:37
�ŏI�X�V 2012/06/5 21:17
�����  2012/03/15 22:02
�o�[�W���� 1.01

 <�X�V����>
 �E2012/06/05 22:48
	�o�O�C��
 �E2012/05/18 21:08
    RunableComponentInterface��typedef��SeenInterface�ɂ���(�\�[�X�R�[�h�̕ύX�̕K�v�Ȃ������A�ύX����)

 �E2012/03/29 13:20
	focusOn�ň������󂯎���悤�ɃC���^�[�t�F�[�X�啝�C��

 �E2012/03/21 17:08
	defalt��focusOn���\�b�h���Ă΂�Ȃ��o�O���C��

 �E2012/03/15 22:02
	���ׂẴC���^�[�t�F�[�X�N���X��
	void focusOn(TCommon& CommonData)
	���\�b�h��
	void focusOn(TCommon& CommonData)
	�ɕύX�B

<�T�v>
��ԕω��𔺂��I�u�W�F�N�g(�퓬��}�b�v�A�����_�C�A���O���邢�̓V�[���̑J�ڂȂ�)��
�ȒP�ɂ����Čn�������Ĉ������߂̃t���[�����[�N�ł��B
���RPG��SLG���ł̗��p��z�肵�Ă��܂��B(���܂葬�x�œK���͎{���Ă��Ȃ�)

<�ˑ��֌W>
boost

<�N���X�\��>
���̃t���[�����[�N��sto(StateTransitionObject�̗�)�Ƃ������O��Ԃɂ܂Ƃ߂��
SeenInterface�N���X�ARunablePieceInterface�N���X�AAbstructStoManager�N���X��3�̎�v�N���X
�y��TManagerTypedef�N���X,AbstructManager�̕⏕�N���X����Ȃ�܂��B 


SeenInterface�N���X�y��RunablePieceInterface�N���X�̓V�[�����Ԃ�
�ǐ��A�C�����₷����ۂ����܂ܕ\������C���^�[�t�F�[�X���A
AbstructStoManager�N���X�͂������������@��񋟂��܂��B
�ȍ~���삷�鑤���}�l�[�W��(AbstructStoManager)�A���삳��鑤(SeenInterface��)���I�u�W�F�N�g�ƌĂт܂��B

<�N���X�̓���y�ё��ݍ�p>
�E�}�l�[�W���̓���
�}�l�[�W���C���X�^���X��������AbstructStoManager�N���X�̃R���X�g���N�^�ɂ��A�������������s����B

1.SeenInterface�𑀍삷��ꍇ
	�t�H�[�J�X�̓����Ă���I�u�W�F�N�g��run���\�b�h���}�l�[�W���ɂ��Ă΂��B

2.MVC���f���ɂ��RunablePieceInterface�𑀍삷��ꍇ
	�t�H�[�J�X�̓����Ă���I�u�W�F�N�g��Model��input���\�b�h���}�l�[�W���ɂ��Ă΂��B
	��
	���ׂĂ�Model��update���\�b�h��referPriority���\�b�h�Őݒ肳�ꂽ���ɌĂ΂��B
	��
	���ׂĂ�View��output���\�b�h���Ă΂�A�t�H�[�J�X�̓����Ă���I�u�W�F�N�g���Ԃ����Ԃ�l���O���ɕԂ����

3.RunablePieceInterface�𑀍삷��ꍇ(�񐄏�)
	�t�H�[�J�X�̓����Ă���I�u�W�F�N�g��input���\�b�h���}�l�[�W���ɂ��Ă΂��B
	��
	���ׂĂ�update���\�b�h��referPriority���\�b�h�Őݒ肳�ꂽ���ɌĂ΂��
	��
	���ׂĂ�output���\�b�h���Ă΂�A�t�H�[�J�X�̓����Ă���I�u�W�F�N�g���Ԃ����Ԃ�l���O���ɕԂ����

�̂悤�ȓ���������ōs���܂��B


<�g����>
1.RunableComponentInterface�y��MVCAdaptor(���邢��RunablePieceInterface)����p�������N���X�ɋ�̓I�ȓ��e���L�q
2.���������I�u�W�F�N�g�ɑΉ�����AbstructRunableComponentManager,AbstructMVCManager,AbstructRunablePieceManager
�̂ǂꂩ���炩��p������Manager�N���X(��1)��create���\�b�h������
(3.�I�v�V������Manager�̊e�ǂݍ��ݏ���������,�K�v�Ȃ�΃R���X�g���N�^��init���\�b�h���Ă�)
4.�I������܂�Manager��run���Ă�(���[�v�ŌĂԂ��Ƃ�z��)
�Ƃ����悤�Ɉ�т������̂ƂȂ��Ă��܂��B

RunablePieceInterface��MVC���f���ɂ���Đ݌v�ł���悤��MVCAdaptor�N���X������܂��B
�����p���邱�Ƃɂ��RunablePieceInterface���悢MVC���f���Ő݌v���ێ琫�����サ�܂��B
��{�I�ɂ������p���Ă��������B
�e���v���[�g������TResult,TCommon�̑���Model<TResult,TCommon>��View<TResult,TCommon>������܂��B
Model��View�����������N���X���e���v���[�g�����Ƃ��ēn�����Ƃɂ�莩���I��RunablePieceInterface�Ƃ���
������N���X��Ԃ��܂��B�Öق̃C���^�[�t�F�[�X�̓w�b�_�����̏ڍׂ����Ă��������B

��1
�e���v���[�g��TResult�ATCommon�ATObjType�͂��ꂼ��
TResult�ɂ�Manager��run�̌��ʂƂ��ĕԂ��^�A
TCommon�ɂ̓}�l�[�W�������I�u�W�F�N�g���m�̋��L�f�[�^�̌^�A
TObjType�̓I�u�W�F�N�g(RunablePieceInterface<TResult,TCommon>,���邢��RunableComponentInterface<TResult,TCommon>)
���w�肷��B

��2
MVCAdaptor��View�ł�TManager��typedef�����N���X�ł���TManagerTypedef���p�����邱�Ƃ𐄏����܂��B


��̓I�Ȏg�p��̓T���v�����������������B

*******************************************************************************/

#include <stdlib.h>
#include <string>
#include <map>
#include <stdexcept>

#include<boost/any.hpp>
#include<boost/noncopyable.hpp>

#pragma warning(disable:4290)

#ifndef FRAMEWORK_STATE_TRANSITION_OBJECT
#define FRAMEWORK_STATE_TRANSITION_OBJECT

#ifdef _MSC_VER 
	#if _MSC_VER <1600
		#define nullptr NULL
	#endif
#endif

namespace sto{

template <class TResult,class TCommon> class RunableComponentInterface;
template <class TResult,class TCommon> class RunablePieceInterface;
template <class TResult,class TCommon,class TObjType> class AbstructManager;
template<typename TResult,typename TCommon,template<typename,typename>class Model,template<typename,typename>class View> class MVCAdaptor;
template<typename TResult,typename TCommon,template<typename,typename>class Objtype>class TManagerTypedef;


//===============================TManagerTypedef===============================
//�T�u�N���X��TManager�ւ�typedef��񋟂���
template<typename TResult,typename TCommon,template<typename,typename>class Objtype>
class TManagerTypedef{
protected:
	typedef sto::AbstructManager<TResult,TCommon,Objtype<TResult,TCommon> > TManager; 	
};

//================SeenInterface(RunableComponentInterface)=====================
//�V�[�����̓Ɨ��x�̍����P��I�u�W�F�N�g��z�肵����r�I�傫�Ȏ��s�P�ʂ̃C���^�[�t�F�[�X�N���X
template <class TResult,class TCommon> class RunableComponentInterface : public TManagerTypedef<TResult,TCommon,sto::RunableComponentInterface>{
public:
	//���s���\�b�h
	//�t�H�[�J�X�������Ă���I�u�W�F�N�g���Ă΂��
	virtual const TResult& run(TManager* Manager,TCommon& CommonData,std::map<std::string,boost::any>& ParameterList)=0;
	
	//�t�H�[�J�X���ڂ����Ƃ��ɍŏ��ɌĂ΂��
	virtual void focusOn(std::map<std::string,boost::any>& ParameterList)=0;
	//�t�H�[�J�X�����ꂽ�Ƃ��ɌĂ΂��
	virtual void focusOut()=0;
		
	//���z�f�X�g���N�^
    virtual ~RunableComponentInterface(){}

};

//RunableComponentInterface��typedef
template <class TResult,class TCommon> 
class SeenInterface :public RunableComponentInterface<TResult,TCommon>{};

//=========================RunablePieceInterface===============================
//�����I�u�W�F�N�g�̕��i��z�肵�������Ȏ��s�P�ʂ̃C���^�[�t�F�[�X�N���X

template <class TResult,class TCommon> class RunablePieceInterface : public TManagerTypedef<TResult,TCommon,sto::RunablePieceInterface>{
public:
	//���̓��\�b�h
	//�L�[���͂ňړ��ȂǂɎg�p�B
	//�I�u�W�F�N�g�Ƀt�H�[�J�X�������Ă���Ƃ��̂݌Ă΂��B
	virtual void input()=0;
	
	//��Ԉێ����\�b�h
	//�����Ƃ��ċ��L�f�[�^���󂯎�邱�Ƃ��ł���B
	//��ɌĂяo����I�u�W�F�N�g�̏�Ԃ�ύX,�ێ�����B
	virtual void update(TCommon& CommonData)=0;
	
	//�o�̓��\�b�h
	//�����Ƃ��ă}�l�[�W���̃|�C���^���󂯎��A�}�l�[�W���̃��\�b�h���ĂԂ��Ƃ��ł���B
	//�����f�[�^�Ɋ�Â��������s���B
	//������Ԃ�ω������邱�Ƃ͂ł��Ȃ��B
	//��ɌĂяo����A�t�H�[�J�X�̓����Ă���I�u�W�F�N�g�͕Ԃ�l�����ɕԂ����Ƃ��ł���B(�t�H�[�J�X�̓����Ă��Ȃ��ꍇ�A�Ԃ�l�͖���)
	virtual const TResult& output(TManager* Manager,std::map<std::string,boost::any>& ParameterList) const =0;

	//�t�H�[�J�X���������Ƃ��̏������s��
	//���̃I�u�W�F�N�g���玩���Ƀt�H�[�J�X���ڂ����Ƃ��ɍŏ��ɌĂ΂��
	virtual void focusOn(std::map<std::string,boost::any>& ParameterList)=0;
	//�t�H�[�J�X�����ꂽ�Ƃ��ɌĂ΂��
	virtual void focusOut()=0;
	
	//�o�͗D�揇�ʂ�Ԃ��֐�
	//���l���傫���قǂ��ォ��o�͂����B�͈͔͂C�ӁB
	virtual int referPriority()=0;
	
	//���z�f�X�g���N�^
    virtual ~RunablePieceInterface(){}

};

//MVC����RunablePieceInterface�ւ̃A�_�v�^
template<typename TResult,typename TCommon,template<typename,typename>class Model,template<typename,typename>class View>
class MVCAdaptor:public sto::RunablePieceInterface<TResult,TCommon>{
public:
	void input(){ModelObject.input();}
	void update(TCommon& CommonData){ModelObject.update(CommonData);}
	//�C���^�[�t�F�[�X�̓s����const�ɂ��Ă��邪�A����const�����o�֐��łȂ��悤�ɂȂ��Ă���B
	const TResult& output(TManager* Manager,std::map<std::string,boost::any>& ParameterList) const{return ViewObject.output(Manager,ParameterList,const_cast<const Model<TResult,TCommon>&>(ModelObject));}
	void focusOn(std::map<std::string,boost::any>& ParameterList){ModelObject.focusOn(ParameterList);ViewObject.focusOn(ParameterList);}
	void focusOut(){ModelObject.focusOut();ViewObject.focusOut();}
	int referPriority(){return ViewObject.referPriority();}
private:
	Model<TResult,TCommon> ModelObject;
	mutable View<TResult,TCommon> ViewObject;
};

/*
template<typename,typename>Model�̈Öق̃C���^�[�t�F�[�X
	void input();
	void update(TCommon& CommonData);
	void focusOn(std::map<std::string,boost::any>& ParameterList);
	void focusOut();
template<typename,typename>View�̈Öق̃C���^�[�t�F�[�X
	TResult& output(TManager*,const Model<TResult,TCommon>&) const;
	void focusOn(CommonData);
	void focusOut();
	int referPriority();
*/



//=================================AbstructStoManager=====================================
//RunablePieceInterface�����RunableComponentInterface�𑀍삷�邽�߂̒��ۃN���X�Q
//�����ڍׂ�AbstructManager

template<typename TResult,typename TCommon>
class AbstructRunableComponentManager:public AbstructManager<TResult,TCommon,sto::RunableComponentInterface<TResult,TCommon> >{};

template<typename TResult,typename TCommon>
class  AbstructSeenManager:public AbstructRunableComponentManager<TResult,TCommon>{};

template<typename TResult,typename TCommon>
class AbstructMVCManager:public AbstructManager<TResult,TCommon,sto::RunablePieceInterface<TResult,TCommon> >{};

template<typename TResult,typename TCommon>
class AbstructRunablePieceManager:public AbstructManager<TResult,TCommon,sto::RunablePieceInterface<TResult,TCommon> >{};






//AbstructStoManager�̓��������ڍ�
template <class TResult,class TCommon,class TObjType> class AbstructManager : private boost::noncopyable{
public:
	//�}�l�[�W���[�����s����
	const TResult& run();
	
	//�t�H�[�J�X�̓����Ă���I�u�W�F�N�g�ύX
	//�ύX�ł��Ȃ���Η�O���o
	//changeFocus(�ύX��I�u�W�F�N�g��)
	void changeFocus(std::string ObjName)  throw(std::invalid_argument);

protected:

	AbstructManager();//�f�t�H���g�R���X�g���N�^
	AbstructManager(TCommon& CommonData_);//CommonData�����������邽�߂̃R���X�g���N�^

 	virtual ~AbstructManager();

	//����������
	//�T�u�N���X�̃R���X�g���N�^�ŌĂԂ��Ƃ𐄏�(�Ă΂Ȃ��Ă��ꉞ�͕K�v���ɌĂ΂��悤�ɂȂ��Ă���)
	void init();//������

	//�I�u�W�F�N�g���}�l�[�W���ɒǉ�
	//�s���ȃI�u�W�F�N�g��ǉ������ꍇ��O���o
	//append(�I�u�W�F�N�g���A�I�u�W�F�N�g�ւ̃|�C���^);
	//name��"default"���w�肷��Ǝ����I�ɂ��ꂪ�ŏ��Ƀt�H�[�J�X�̓������I�u�W�F�N�g�ɂȂ�B
	//�܂��A�ȈՃK�[�x�[�W�R���N�^���������Ă��邽�ߓ��I�m�ۂ����|�C���^���������Ȃ�
	void append(std::string,TObjType*) throw(std::invalid_argument);

	/********************�ȉ��̊֐��̓I�[�o�[���C�h���Ďg�p********************/
	//�}�l�[�W���ɃR���|�W�V��������I�u�W�F�N�g�𐶐��A�ǉ�����(append�𗘗p)�t�@�N�g�����\�b�h�B�K�{�B
	virtual void create()=0;

	//�ȉ��̓f�[�^�ǂݍ��݌n�̃I�v�V�����̃��\�b�h(�f�[�^�̃��[�h���Ǐ�������)
	
	//�f�[�^�Ȃǂ�ǂݍ��ޏ������L�q
	//�ǂ̓ǂݍ��ݏ���������ɌĂ΂��
	virtual void loadData(){}
	//�摜��ǂݍ��ޏ������L�q
	virtual void loadImage(){}
	//�T�E���h�֌W��ǂݍ��ޏ������L�q
	virtual void loadSound(){}
	//�t�H���g��ǂݍ��ޏ������L�q
	virtual void loadFont(){}


private:
						
	bool CreatedFlagOn;//�}�l�[�W���̎��̂�Create�������̃t���O
	
	TCommon& CommonData;//���ʃf�[�^
	TCommon DummyCommonData;//���ʃf�[�^
	
	TResult& ResultData;//���ʃf�[�^
	TResult DummyData;//�_�~�[�f�[�^
	
	std::map<std::string,boost::any> ParameterList;//forcusOn�ɓn��������

	std::map<std::string,TObjType*> ObjectMap;//�I�u�W�F�N�g�̖��O�ƃ|�C���^�̘A�z�z�� 

	std::string SelectedObjectName;//���ݑI������Ă���I�u�W�F�N�g��

	//run���\�b�h���p�[�c�̃^�C�v�ɂ���ĐÓI�ύX���邽�߂̓����N���X
	template <class T,class S,class U>
	class RunFunction{
	public:
        static void run(AbstructManager<T,S,U>& Self){}
	};

};


}//���O��Ԃ̏I���


/*******************************************************************************
*                                                                              *
*                                ���\�b�h��`��                                *
*                                                                              *
*******************************************************************************/


//============================default�R���X�g���N�^=============================
template <class TResult,class TCommon,class TObjType>
sto::AbstructManager<TResult,TCommon,TObjType>::AbstructManager():
	DummyData(),
	ResultData(DummyData),
	CommonData(DummyCommonData)
	{
	
	CreatedFlagOn=false;
	SelectedObjectName="default";

	
	}
template <class TResult,class TCommon,class TObjType>
sto::AbstructManager<TResult,TCommon,TObjType>::AbstructManager(TCommon& CommonData_):
	DummyData(),
	ResultData(DummyData),
	CommonData(CommonData_)
	{
	
	CreatedFlagOn=false;
	SelectedObjectName="default";
	
	}



//===============================�f�X�g���N�^====================================
template <class TResult,class TCommon,class TObjType>
sto::AbstructManager<TResult,TCommon,TObjType>::~AbstructManager(){	
	{
		std::map<std::string,TObjType*>::iterator it = ObjectMap.begin();
		while( it != ObjectMap.end() ){
			delete((*it).second);
			(*it).second=nullptr;
			it++;
    	}
	}
	

}

//===================================init()======================================
//������
template <class TResult,class TCommon,class TObjType>
void sto::AbstructManager<TResult,TCommon,TObjType>::init(){

	loadData();
	loadImage();
	loadSound();
	loadFont();
	create();
	CreatedFlagOn=true;	 
	ObjectMap[SelectedObjectName]->focusOn(ParameterList);

	}


//==================================append()======================================
template <class TResult,class TCommon,class TObjType>
void sto::AbstructManager<TResult,TCommon,TObjType>::append(std::string ObjName,TObjType* AppendObj) throw(std::invalid_argument){
	ObjectMap.insert(std::map<std::string,TObjType*>::value_type(ObjName,AppendObj));
}



//=====================================changeFocus=================================


template <class TResult,class TCommon,class TObjType>
void sto::AbstructManager<TResult,TCommon,TObjType>::changeFocus(std::string ObjName) throw(std::invalid_argument){

	if (CreatedFlagOn==false){
		init();
	}

	if (ObjectMap.find(ObjName)==ObjectMap.end()) throw std::invalid_argument("�w�肵�����O�̃I�u�W�F�N�g��������Ȃ�");
	
	ObjectMap[SelectedObjectName]->focusOut();
	SelectedObjectName=ObjName;
	ObjectMap[SelectedObjectName]->focusOn(ParameterList);
	
	
}

//=======================================run=======================================

template<class TResult,class TCommon,class TObjType>
const TResult& sto::AbstructManager<TResult,TCommon,TObjType>::run(){

	if (CreatedFlagOn==false){
		init();
	}

	//ParameterList����ɋ�ɕۂ�
	if(!ParameterList.empty()) ParameterList.clear();

	RunFunction<TResult,TCommon,TObjType>::run(*this);


	return ResultData;
}

//===============================run�̓��ꉻ==================================

template<class TResult,class TCommon,class TObjType>
template <class T,class S>
class sto::AbstructManager<TResult,TCommon,TObjType>::RunFunction<T,S,sto::RunablePieceInterface<T,S> >{
public:
	static void run(AbstructManager<T,S,sto::RunablePieceInterface<T,S> >& Self){
	
		Self.ObjectMap[Self.SelectedObjectName]->input();//����
	    

		//���e�ێ��u���b�N
		{
			unsigned int Counter=0;//�\�������I�u�W�F�N�g�̐�
			int NowDrawLevel=0;	
			
			while(Counter<Self.ObjectMap.size()){
				std::map<std::string,RunablePieceInterface<TResult,TCommon>*>::iterator it = Self.ObjectMap.begin();
					while( it != Self.ObjectMap.end() ){
						if ((((*it).second)->referPriority())==NowDrawLevel){
							((*it).second)->update(Self.CommonData);
							Counter++;
						}
						it++;
					}
				NowDrawLevel++;	
			}
		}
		
		//�o�̓u���b�N	
		{
			unsigned int Counter=0;//�\�������I�u�W�F�N�g�̐�
			int NowDrawLevel=0;	
			//�o��
			Counter=0;
			NowDrawLevel=0;
			while(Counter<Self.ObjectMap.size()){
				std::map<std::string,RunablePieceInterface<TResult,TCommon>*>::iterator it = Self.ObjectMap.begin();
					while( it != Self.ObjectMap.end() ){
						if ((((*it).second)->referPriority())==NowDrawLevel){
							if ((*it).first==Self.SelectedObjectName){
								Self.ResultData=((*it).second)->output(&Self,Self.ParameterList);
							}else{
								((*it).second)->output(&Self,Self.ParameterList);
							}
							Counter++;
						}
						it++;
					}
				NowDrawLevel++;	
			}
		}
	}


};

template<class TResult,class TCommon,class TObjType>
template <class T,class S>
class sto::AbstructManager<TResult,TCommon,TObjType>::RunFunction<T,S,sto::RunableComponentInterface<T,S> >{
public:
	static void run(AbstructManager<T,S,sto::RunableComponentInterface<T,S> >& Self){
		Self.ResultData=Self.ObjectMap[Self.SelectedObjectName]->run(&Self,Self.CommonData,Self.ParameterList);
	}
};




#endif
