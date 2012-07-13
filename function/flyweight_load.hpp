/*******************************************************************************
                  DxLib�̓ǂݍ��݌n�̊֐���Flyweight�ȃ��b�p

Copyright (C) 2011 ���\�t�g

�쐬�� ������A�F�V(HN���Ƃōl����)
�����VC++ 2008 Express Edition
�쐬���� 2011/02/19 17:31
�ŏI�X�V 2011/02/19 17:31

<�T�v>
DxLib�̓ǂݍ��݊֐��n��Flyweight�ň�����悤�ɂ����t�@���N�^�Q�ł��B

*******************************************************************************/


#include "DxLib.h"
#include<string>
#include<map>
#include <cassert>

#ifndef GARD_FLYWEIGHT_LOAD
#define GARD_FLYWEIGHT_LOAD

namespace function{


//================================FlyweightGraph================================
//LoadGraph��Flyweight�ň������߂̃N���X
//�O���t�B�b�N�n���h��=FlyweightGraph::Load("�t�@�C����");
class FlyweightGraph{
public:
	static int Load(std::string FileName);
	//�O���t�B�b�N�n���h�����폜����
	static void Delete(std::string FileName){DeleteGraph(getInstance().GrHwnd[FileName]);getInstance().GrHwnd.erase(FileName);};

private:
	std::map<std::string,int> GrHwnd;
	static FlyweightGraph& getInstance();
	
	FlyweightGraph(){}
    FlyweightGraph(const FlyweightGraph& rhs);
    FlyweightGraph& operator=(const FlyweightGraph& rhs);
};

class FlyweightSound{
public:
	// �T�E���h�n���h�����擾����
	static int Load(std::string FileName);
	// �T�E���h�n���h�����폜����
	static void Delete(std::string FileName){
		DeleteSoundMem(getInstance().SdHwnd[FileName]);
		getInstance().SdHwnd.erase(FileName);
	};


private:
	std::map<std::string,int> SdHwnd;
	static FlyweightSound& getInstance();

	FlyweightSound(){}
	FlyweightSound(const FlyweightSound& rhs);
	FlyweightSound& operator=(const FlyweightSound& rhs);

};

//===============================FlyweightDivGraph==============================
//LoadDivGraph��Flyweight�ň������߂̃N���X
//FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::Load("�t�@�C����",�O���t�B�b�NHandle���i�[����|�C���^);
template<int AllNum,int XNum,int YNum,int XSize,int YSize>
class FlyweightDivGraph{
public:
	static void Load(std::string FileName,int *HandleBuf);
	~FlyweightDivGraph();

private:
	std::map<std::string,int*> GrHwnd;
	static FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>& getInstance();

	
	FlyweightDivGraph(){}
    FlyweightDivGraph(const FlyweightDivGraph& rhs);
    FlyweightDivGraph& operator=(const FlyweightDivGraph& rhs);
};

//=================================FlyweightFont================================
//CreateFontToHandle��Flyweight�ň������߂̃N���X
//FlyweightDivGraph<Size,Thick,FontType>::Load("�쐬����t�H���g��");
template<int Size,int Thick,int FontType>
class FlyweightFont{
public:
	static int Load(std::string FontName);
	//NULL���n���ꂽ�Ƃ��̂��߂̃I�[�o���C�h(char*�łȂ��͉̂������B���ɂȂ�̂�h������)
	static int Load(int* FontName);
	~FlyweightFont(){}

private:
	std::map<std::string,int> FontHwnd;
	static FlyweightFont<Size,Thick,FontType>& getInstance();

	
	FlyweightFont(){}
    FlyweightFont(const FlyweightFont& rhs);
    FlyweightFont& operator=(const FlyweightFont& rhs);
};



}//function�̏I���



//=================================���\�b�h��`================================


//==============================FlyweightDivGraph==============================
template<int AllNum,int XNum,int YNum,int XSize,int YSize>
void function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::Load(std::string FileName,int *HandleBuf){
	static FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize> &instance=getInstance();
    
	if (instance.GrHwnd.count(FileName)==0){
		int *GrBuf=new int[AllNum];//�o�b�t�@

		LoadDivGraph(FileName.c_str(),AllNum,XNum,YNum,XSize,YSize,GrBuf);
		instance.GrHwnd.insert( std::map<std::string,int*>::value_type(FileName,GrBuf));
	}
			
	int *TmpBuffer=instance.GrHwnd[FileName];//�ꎞ�o�b�t�@
	for(int i=0;i<AllNum;i++){
		HandleBuf[i]=TmpBuffer[i];
	}
		
	return;
}


template<int AllNum,int XNum,int YNum,int XSize,int YSize>
function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::~FlyweightDivGraph(){
	std::map<std::string,int*>::iterator it = GrHwnd.begin();
	while( it != GrHwnd.end() ){
		delete [] (*it).second;
		++it;
	}
	return;
}

template<int AllNum,int XNum,int YNum,int XSize,int YSize>
function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>& function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::getInstance(){
	static FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize> instance;
	return instance;
}

//=================================FlyweightFont================================
template<int Size,int Thick,int FontType>
int function::FlyweightFont<Size,Thick,FontType>::Load(std::string FontName){
    	FlyweightFont<Size,Thick,FontType> &instance=getInstance();

		if (instance.FontHwnd.count(FontName)==0){
			instance.FontHwnd.insert( std::map<std::string,int>::value_type(FontName,CreateFontToHandle(FontName.c_str(),Size,Thick,FontType)));
		}
    	return instance.FontHwnd[FontName];
}

template<int Size,int Thick,int FontType>
int function::FlyweightFont<Size,Thick,FontType>::Load(int* FontName){
		assert(FontName==NULL);
    	FlyweightFont<Size,Thick,FontType> &instance=getInstance();

		if (instance.FontHwnd.count("")==0){
			instance.FontHwnd.insert( std::map<std::string,int>::value_type("",CreateFontToHandle(NULL,Size,Thick,FontType)));
		}
    	return instance.FontHwnd[""];
}

template<int Size,int Thick,int FontType>
function::FlyweightFont<Size,Thick,FontType>& function::FlyweightFont<Size,Thick,FontType>::getInstance(){
	static function::FlyweightFont<Size,Thick,FontType> instance;
	return instance;
}

#endif
