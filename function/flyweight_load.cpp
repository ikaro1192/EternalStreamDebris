#include "flyweight_load.hpp"


int function::FlyweightGraph::Load(std::string FileName){
    	FlyweightGraph &instance=getInstance();

		if (instance.GrHwnd.count(FileName)==0){
			instance.GrHwnd.insert( std::map<std::string,int>::value_type(FileName,LoadGraph(FileName.c_str())));
		}
    	return instance.GrHwnd[FileName];
}

function::FlyweightGraph& function::FlyweightGraph::getInstance(){
	static function::FlyweightGraph instance;
	return instance;
}

int function::FlyweightSound::Load(std::string FileName){
    	FlyweightSound &instance=getInstance();
	
	// map����"FileName"�ƈ�v����n���h�������݂��Ȃ��Ȃ�	
	if (instance.SdHwnd.count(FileName)==0){
		// "FileName"���L�[�A�ǂݍ��񂾃n���h����l�Ƃ��āA�ۑ�
		instance.SdHwnd.insert( std::map<std::string,int>::value_type(FileName,LoadSoundMem(FileName.c_str())));
	}
    	
	return instance.SdHwnd[FileName];
}

function::FlyweightSound& function::FlyweightSound::getInstance(){
	static function::FlyweightSound instance;
	return instance;
}