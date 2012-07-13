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
	
	// map中の"FileName"と一致するハンドルが存在しないなら	
	if (instance.SdHwnd.count(FileName)==0){
		// "FileName"をキー、読み込んだハンドルを値として、保存
		instance.SdHwnd.insert( std::map<std::string,int>::value_type(FileName,LoadSoundMem(FileName.c_str())));
	}
    	
	return instance.SdHwnd[FileName];
}

function::FlyweightSound& function::FlyweightSound::getInstance(){
	static function::FlyweightSound instance;
	return instance;
}