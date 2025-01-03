#include "Audio.h"






static uint32_t audioIndex;

Audio* Audio::GetInstance() {
	static Audio instance;
	return &instance;
}

void Audio::CreateSubmixVoice(uint32_t channel) {
	uint32_t channels = channel;
	uint32_t sampleRate = 44100;



	HRESULT hr = {};
	hr = Audio::GetInstance()->xAudio2_->CreateSubmixVoice(&Audio::GetInstance()->submixVoice_[channel], channels, sampleRate);
	assert(SUCCEEDED(hr));

}

//初期化
//これはDirecX初期化の後に入れてね
void Audio::Initialize() {

	//MediaFundationの初期化
	HRESULT hr = {};
	hr=MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);
	assert(SUCCEEDED(hr));

	//XAudioのエンジンのインスタンスを生成
	hr = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));

	//マスターボイスを生成
	hr = xAudio2_->CreateMasteringVoice(&masterVoice_);
	assert(SUCCEEDED(hr));

	//スピーカ構成を取得
	masterVoice_->GetChannelMask(&dwChannelMask_);

	
	

	//一度全部0に初期化
	for (int i = 0; i < 8; i++) {
		outputMatrix_[i] = 0;
	}

	//サブミックスボイス(DTMでのバス)をここで作る
	//64くらいあれば十分でしょう。多すぎてもメモリの無駄になってしまうし
	//FLStudioと同じように128あれば良いなと思ったが
	for (int i = 1; i < SUBMIXVOICE_AMOUNT_; ++i) {

		CreateSubmixVoice(i);
	}
	



}



#pragma region 実際に使う関数

#pragma region 基本セット
//読み込み
uint32_t Audio::LoadWave(const char* fileName) {

	//16,24,32bitは読み込み出来た
	//64bitも読み込み出来るようにしたいと思ったが一般的に使われないらしい
	//だから32が最大で良いかも。
	//64bitを書き出せるCakewslkすご


	//一度読み込んだものは２度読み込まず返すだけ
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		if (Audio::GetInstance()->audioInformation_[i].name_ == fileName) {
			return Audio::GetInstance()->audioInformation_[i].audioHandle_;
		}
	}
	//audioHandle_++;
	audioIndex++;

	//記録
	Audio::GetInstance()->audioInformation_[audioIndex].name_ = fileName;
	Audio::GetInstance()->audioInformation_[audioIndex].audioHandle_ = audioIndex;


#pragma region １,ファイルオープン
	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバイナリモードで開く
	file.open(fileName, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	assert(file.is_open());

#pragma endregion

#pragma region ２,wavデータ読み込み

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	//何かここ空白入れないとダメらしい
	//後ろが4だからかな・・
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);


	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0) {
		//読み込み位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));

	}

	//メインのデータチャンク
	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	//Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
#pragma endregion

#pragma region ３,Waveファイルを閉じる
	file.close();


#pragma endregion




#pragma region 読み込んだ音声データを返す

	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex = format.fmt;
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.bufferSize = data.size;


	//波形フォーマットを基にSourceVoiceの生成
	HRESULT hr{};
	hr = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_,
		&Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex);
	assert(SUCCEEDED(hr));


	//フィルターを使う場合
	//後でFilterを使う場合のロードを作りたい
	hr = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_,
		&Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex, XAUDIO2_VOICE_USEFILTER, 16.0f);

	assert(SUCCEEDED(hr));

	return audioIndex;

#pragma endregion



}

uint32_t Audio::LoadWave(const char* fileName, uint32_t effectType) {
	effectType;
	//16,24,32bitは読み込み出来た
	//64bitも読み込み出来るようにしたいと思ったが一般的に使われないらしい
	//だから32が最大で良いかも。
	//64bitを書き出せるCakewslkすご


	//一度読み込んだものは２度読み込まず返すだけ
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		if (Audio::GetInstance()->audioInformation_[i].name_ == fileName) {
			return Audio::GetInstance()->audioInformation_[i].audioHandle_;
		}
	}
	//audioHandle_++;
	audioIndex++;

	//記録
	Audio::GetInstance()->audioInformation_[audioIndex].name_ = fileName;
	Audio::GetInstance()->audioInformation_[audioIndex].audioHandle_ = audioIndex;


#pragma region １,ファイルオープン
	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバイナリモードで開く
	file.open(fileName, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	assert(file.is_open());

#pragma endregion

#pragma region ２,wavデータ読み込み

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	//何かここ空白入れないとダメらしい
	//後ろが4だからかな・・
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);


	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0) {
		//読み込み位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));

	}

	//メインのデータチャンク
	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	//Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
#pragma endregion

#pragma region ３,Waveファイルを閉じる
	file.close();


#pragma endregion




#pragma region 読み込んだ音声データを返す

	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex = format.fmt;
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.bufferSize = data.size;


	//波形フォーマットを基にSourceVoiceの生成
	HRESULT hr{};

	hr = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_,
		&Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex, XAUDIO2_VOICE_USEFILTER, 16.0f);

	assert(SUCCEEDED(hr));

	return audioIndex;

#pragma endregion


}

uint32_t Audio::LoadMP3(const WCHAR* fileName){
	//効果音系にはMP3は良いけど
	//ループにはおすすめできないらしい。末端に無音が入るため。
	

	


	//一度読み込んだものは２度読み込まず返すだけ
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		if (Audio::GetInstance()->audioInformation_[i].mp3FileName_ == fileName) {
			return Audio::GetInstance()->audioInformation_[i].audioHandle_;
		}
	}

	audioIndex++;

	//記録
	Audio::GetInstance()->audioInformation_[audioIndex].mp3FileName_ = fileName;
	Audio::GetInstance()->audioInformation_[audioIndex].audioHandle_ = audioIndex;

	HRESULT hr = {};

	//ソースリーダーの作成
	hr = MFCreateSourceReaderFromURL(fileName, nullptr, &Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_);
	assert(SUCCEEDED(hr));



	//メディアタイプの取得
	IMFMediaType* pMFMediaType{ nullptr };
	MFCreateMediaType(&pMFMediaType);
	pMFMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	pMFMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_->SetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, pMFMediaType);

	pMFMediaType->Release();
	pMFMediaType = nullptr;
	Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_->GetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &pMFMediaType);

	//オーディオデータ形式の作成
	WAVEFORMATEX* waveFormat{};
	MFCreateWaveFormatExFromMFMediaType(pMFMediaType, &waveFormat, nullptr);


	
	while (true)
	{
		IMFSample* pMFSample{ nullptr };
		DWORD dwStreamFlags{ 0 };
		Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_->ReadSample(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &dwStreamFlags, nullptr, &pMFSample);

		if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			break;
		}

		IMFMediaBuffer* pMFMediaBuffer{ nullptr };
		pMFSample->ConvertToContiguousBuffer(&pMFMediaBuffer);

		BYTE* pBuffer{ nullptr };
		DWORD cbCurrentLength{ 0 };
		pMFMediaBuffer->Lock(&pBuffer, nullptr, &cbCurrentLength);

		Audio::GetInstance()->audioInformation_[audioIndex].mediaData.resize(Audio::GetInstance()->audioInformation_[audioIndex].mediaData.size() + cbCurrentLength);
		memcpy(Audio::GetInstance()->audioInformation_[audioIndex].mediaData.data() + Audio::GetInstance()->audioInformation_[audioIndex].mediaData.size() - cbCurrentLength, pBuffer, cbCurrentLength);

		pMFMediaBuffer->Unlock();

		pMFMediaBuffer->Release();
		pMFSample->Release();
	}

	Audio::GetInstance()->xAudio2_->CreateSourceVoice(&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_, waveFormat);


	return audioIndex;
}

//音声再生
void Audio::PlayWave(uint32_t audioHandle, bool isLoop) {
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->FlushSourceBuffers();
	assert(SUCCEEDED(hr));
	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (isLoop == true) {
		//ずっとループさせたいならLoopCountにXAUDIO2_LOOP_INFINITEをいれよう
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else{
		buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	}
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));
}

//ループ回数設定版
void Audio::PlayWave(uint32_t audioHandle, int32_t loopCount) {
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->FlushSourceBuffers();
	assert(SUCCEEDED(hr));

	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	//1回多くなっているので-1してあげた方が良いかも
	//1でfalseの場合と同じ
	buffer.LoopCount = loopCount - 1;

	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));
}

void Audio::PlayMP3(uint32_t audioHandle,bool isLoop){
	//MP3はループしない方が良いとのこと
	//一応用意するけど使わないかも
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->FlushSourceBuffers();
	assert(SUCCEEDED(hr));

	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = Audio::GetInstance()->audioInformation_[audioHandle].mediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(Audio::GetInstance()->audioInformation_[audioHandle].mediaData.size());
	if (isLoop == true) {
		//ずっとループさせたいならLoopCountにXAUDIO2_LOOP_INFINITEをいれよう
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else{
		buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	}


	hr = Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);

	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);
	assert(SUCCEEDED(hr));
}

void Audio::PlayMP3(uint32_t audioHandle, uint32_t loopCount){
	//MP3はループしない方が良いとのこと
	//一応用意するけど使わないかも

	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->FlushSourceBuffers();
	assert(SUCCEEDED(hr));
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = Audio::GetInstance()->audioInformation_[audioHandle].mediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(Audio::GetInstance()->audioInformation_[audioHandle].mediaData.size());
	//ここでループ回数を設定
	//1回多くなっているので-1してあげた方が良いかも
	//1でfalseの場合と同じ
	buffer.LoopCount = loopCount - 1;



	hr = Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);

	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);
	assert(SUCCEEDED(hr));
}

void Audio::PauseWave(uint32_t audioHandle) {
	HRESULT hr{};
	//いきなり停止させて残響とかのエフェクトも停止させたら違和感ある
	//だからXAUDIO2_PLAY_TAILSを入れて余韻も残す
	hr = audioInformation_[audioHandle].pSourceVoice_->Stop(XAUDIO2_PLAY_TAILS);
	assert(SUCCEEDED(hr));
}

void Audio::ResumeWave(uint32_t audioHandle) {
	//とはいってもただ再生しているだけ
	//PlayWaveのbufferが無い版

	HRESULT hr{};
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);
	assert(SUCCEEDED(hr));
}

//音声停止
void Audio::StopWave(uint32_t audioHandle) {
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->Stop();
	assert(SUCCEEDED(hr));
}

#pragma endregion


#pragma region ループ
void Audio::ExitLoop(uint32_t audioHandle) {
	HRESULT hr{};
	//ExitLoop関数でループを抜ける
	hr = audioInformation_[audioHandle].pSourceVoice_->ExitLoop();
	assert(SUCCEEDED(hr));
}


void Audio::AfterLoopPlayWave(uint32_t audioHandle, float second) {
	//別名サスティンループというらしい
	//シンセとかにあるサスティンと関係があるのかな

	//後半ループするよ
	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	//長いので新しく変数を作って分かりやすくする
	int samplingRate = Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex.nSamplesPerSec;

	//ここでループしたい位置を設定してあげる
	buffer.LoopBegin = uint32_t(second * samplingRate);



	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));

}


void Audio::BeforeLoopPlayWave(uint32_t audioHandle, float lengthSecond) {
	//別名サスティンループというらしい
	//シンセとかにあるサスティンと関係があるのかな
	//こっちは前半でループ

	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	//長いので新しく変数を作って分かりやすくする
	int samplingRate = Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex.nSamplesPerSec;

	//ここでループしたい位置を設定してあげる
	//ここfloatにしたいけど元々がuint32だから無理そう
	buffer.LoopBegin = 0;
	buffer.LoopLength = uint32_t(lengthSecond * samplingRate);



	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	assert(SUCCEEDED(hr));
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));

}


void Audio::PartlyLoopPlayWave(uint32_t audioHandle, float start, float lengthSecond) {
	//別名サスティンループというらしい
	//シンセとかにあるサスティンと関係があるのかな
	//この関数は部分ループ
	
	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	//長いので新しく変数を作って分かりやすくする
	int samplingRate = Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex.nSamplesPerSec;

	//ここでループしたい位置を設定してあげる
	//ここfloatにしたいけど元々がuint32だから無理そう
	buffer.LoopBegin = uint32_t(start * samplingRate);;
	buffer.LoopLength = uint32_t(lengthSecond * samplingRate);



	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));
}

#pragma endregion

//一応マイナスにも出来るらしい
//位相の反転するために使うらしい。使い道は分からない。
//音量を変える
void Audio::ChangeVolume(uint32_t audioHandle, float volume) {

	HRESULT hr = {};
	hr = audioInformation_[audioHandle].pSourceVoice_->SetVolume(volume);
	assert(SUCCEEDED(hr));
}

//ピッチの変更(滑らか)
void Audio::ChangeFrequency(uint32_t audioHandle, float ratio) {
	HRESULT hr{};

	//これより上がらなかった
	ratio = max(ratio, 2.0f);

	//これより下がらなかった
	ratio = min(ratio, 0.0f);


	hr = audioInformation_[audioHandle].pSourceVoice_->SetFrequencyRatio(ratio);
	assert(SUCCEEDED(hr));
}

//ピッチの変更
//シンセとかのように段階的に出来るよ
void Audio::ChangePitch(uint32_t audioHandle, int32_t scale) {

	HRESULT hr{};
	float ratio = 1.0f;

	//入力された値がプラスだった場合
	if (scale >= 0) {
		//プラスのピッチの方を探す
		for (int32_t i = 0; i < SCALE_AMOUNT_; i++) {
			if (scale == i) {
				ratio = SEMITONE_RATIO_[i];
				break;
			}

		}
		//12以上は上がらなかった
		if (scale > 12) {
			ratio = SEMITONE_RATIO_[12];
		}

	}
	//入力された値がマイナスだった場合
	else if (scale < 0) {
		//マイナスのピッチの方を探す
		for (int32_t i = 0; i < SCALE_AMOUNT_; i++) {
			if (scale == -i) {
				ratio = MINUS_SEMITONE_RATION[i];
				break;
			}

		}
		//-12以上は下がらなかった
		if (scale < -12) {
			ratio = MINUS_SEMITONE_RATION[12];
		}
	}


	hr = audioInformation_[audioHandle].pSourceVoice_->SetFrequencyRatio(ratio);
	assert(SUCCEEDED(hr));
}

void Audio::StretchAndPitch(uint32_t audioHandle, float timeRatio, float pitchRatio){
	// タイムストレッチとピッチ調整を行うパラメータを設定する
	XAUDIO2_VOICE_STATE state;
	Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->GetState(&state);
	Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->Stop(0);
	Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->FlushSourceBuffers();

	// タイムストレッチとピッチ調整を行う
	Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->SetFrequencyRatio(timeRatio * pitchRatio);

	// 再生を再開する
	Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->Start(0);
}

//Pan振り
void Audio::SetPan(uint32_t audioHandle, float_t pan) {

	//左右のスピーカー間の目的のパンに基づき送信レベルを計算
	left_ = 0.5f - pan / 2.0f;
	right_ = 0.5f + pan / 2.0f;
	switch (dwChannelMask_)
	{
	case SPEAKER_MONO:
		outputMatrix_[0] = 1.0f;
		break;
	case SPEAKER_STEREO:
	case SPEAKER_2POINT1:
	case SPEAKER_SURROUND:
		outputMatrix_[1] = left_;
		outputMatrix_[2] = right_;

		break;
	case SPEAKER_QUAD:
		outputMatrix_[0] = left_;
		outputMatrix_[1] = right_;
		outputMatrix_[2] = left_;
		outputMatrix_[3] = right_;
		break;
	case SPEAKER_4POINT1:
		outputMatrix_[0] = left_;
		outputMatrix_[1] = right_;
		outputMatrix_[3] = left_;
		outputMatrix_[4] = right_;
		break;
	case SPEAKER_5POINT1:
	case SPEAKER_7POINT1:
	case SPEAKER_5POINT1_SURROUND:
		outputMatrix_[0] = left_;
		outputMatrix_[1] = right_;
		outputMatrix_[4] = left_;
		outputMatrix_[5] = right_;
		break;
	case SPEAKER_7POINT1_SURROUND:
		outputMatrix_[0] = left_;
		outputMatrix_[1] = right_;
		outputMatrix_[4] = left_;
		outputMatrix_[5] = right_;
		outputMatrix_[6] = left_;
		outputMatrix_[7] = right_;
		break;
	}


#pragma region 解説
	//調べても良く分からなかったのでChatGPTに聞いた
	//outputMatrix_[0]: 主にモノラル音声の場合に使用され、すべての音声を単一のスピーカーに送信します。
	//outputMatrix_[1] : ステレオ音声の場合、左側のスピーカーに対する音声の振幅を指定します。
	//outputMatrix_[2] : ステレオ音声の場合、右側のスピーカーに対する音声の振幅を指定します。
	//outputMatrix_[3] : クアッドフォニックスシステムの場合、左前のスピーカーに対する音声の振幅を指定します。
	//outputMatrix_[4] : クアッドフォニックスシステムの場合、右前のスピーカーに対する音声の振幅を指定します。
	//outputMatrix_[5] : クアッドフォニックスシステムの場合、左後ろのスピーカーに対する音声の振幅を指定します。
	//outputMatrix_[6] : クアッドフォニックスシステムの場合、右後ろのスピーカーに対する音声の振幅を指定します。
	//outputMatrix_[7] : 7.1サラウンドシステムなどのように、サラウンドサウンドをサポートするシステムにおいて、
	//	追加のサラウンドスピーカーに対する音声の振幅を指定するためのものです。
	//	通常、これはセンターバックスピーカーに対する音声の振幅を制御するために使用されます。

	//公式嘘ついてる・・
	//0,1だけだと左しかできないし。

	//普通のスピーカーは1,2を使う。

#pragma endregion

	XAUDIO2_VOICE_DETAILS voiceDetails;
	audioInformation_[audioHandle].pSourceVoice_->GetVoiceDetails(&voiceDetails);

	XAUDIO2_VOICE_DETAILS masterVoiiceDetails;
	masterVoice_->GetVoiceDetails(&masterVoiiceDetails);

	audioInformation_[audioHandle].pSourceVoice_->SetOutputMatrix(
		NULL, voiceDetails.InputChannels,
		masterVoiiceDetails.InputChannels,
		outputMatrix_);

}

void Audio::SetLowPassFilter(uint32_t audioHandle, float cutOff) {
	//いきなり効果アリにすると違和感あるよね
	//LowPassは最初「1.0f」にした方が良いかも
	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if(cutOff < 0.0f){
		newCutOff = 0.0f;
	}

	//このままだとは7500Hzから下しか掛けられないらしい
	XAUDIO2_FILTER_PARAMETERS FilterParams; //フィルタ指示構造体
	FilterParams.Type = XAUDIO2_FILTER_TYPE::LowPassFilter;
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = 1.4142f;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetLowPassFilter(uint32_t audioHandle, float cutOff, float oneOverQ){
	//いきなり効果アリにすると違和感あるよね
	//LowPassは最初「1.0f」にした方が良いかも
	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	//このままだとは7500Hzから下しか掛けられないらしい
	XAUDIO2_FILTER_PARAMETERS FilterParams; //フィルタ指示構造体
	FilterParams.Type = XAUDIO2_FILTER_TYPE::LowPassFilter;
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = oneOverQ;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetHighPassFilter(uint32_t audioHandle, float cutOff){
	//いきなり効果アリにすると違和感あるよね
	//HighPassは最初「0.0f」にした方が良いかも


	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	XAUDIO2_FILTER_PARAMETERS FilterParams;
	FilterParams.Type = XAUDIO2_FILTER_TYPE::HighPassFilter;
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = 1.4142f;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetHighPassFilter(uint32_t audioHandle, float cutOff, float oneOverQ){
	//いきなり効果アリにすると違和感あるよね
	//HighPassは最初「0.0f」にした方が良いかも


	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	XAUDIO2_FILTER_PARAMETERS FilterParams;
	FilterParams.Type = XAUDIO2_FILTER_TYPE::HighPassFilter;
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = oneOverQ;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetBandPassFilter(uint32_t audioHandle, float cutOff){
	//いきなり効果アリにすると違和感あるよね

	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	XAUDIO2_FILTER_PARAMETERS FilterParams;
	FilterParams.Type = XAUDIO2_FILTER_TYPE::BandPassFilter;
	//0.5f
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = 1.0f;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetBandPassFilter(uint32_t audioHandle, float cutOff, float oneOverQ){
	//いきなり効果アリにすると違和感あるよね

	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	XAUDIO2_FILTER_PARAMETERS FilterParams;
	FilterParams.Type = XAUDIO2_FILTER_TYPE::NotchFilter;;
	//0.5f
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = oneOverQ;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetNotchFilter(uint32_t audioHandle, float cutOff){
	//いきなり効果アリにすると違和感あるよね

	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	XAUDIO2_FILTER_PARAMETERS FilterParams;
	FilterParams.Type = XAUDIO2_FILTER_TYPE::BandPassFilter;
	//0.5f
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = 1.0f;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}

void Audio::SetNotchFilter(uint32_t audioHandle, float cutOff, float oneOverQ){
	//いきなり効果アリにすると違和感あるよね

	float newCutOff = cutOff;
	if (cutOff > 1.0f) {
		newCutOff = 1.0f;
	}
	else if (cutOff < 0.0f) {
		newCutOff = 0.0f;
	}

	XAUDIO2_FILTER_PARAMETERS FilterParams;
	FilterParams.Type = XAUDIO2_FILTER_TYPE::BandPassFilter;
	//0.5f
	FilterParams.Frequency = newCutOff;
	FilterParams.OneOverQ = oneOverQ;
	audioInformation_[audioHandle].pSourceVoice_->SetFilterParameters(&FilterParams);
}



void Audio::SendChannels(uint32_t audioHandle,uint32_t channelNumber){
	XAUDIO2_SEND_DESCRIPTOR send = { 0, Audio::GetInstance()->submixVoice_[0]};
	XAUDIO2_VOICE_SENDS sendlist = { channelNumber, &send };

	//HRESULT hr = {};
	audioInformation_[audioHandle].pSourceVoice_->SetOutputVoices(&sendlist);
	//assert(SUCCEEDED(hr));
}

void Audio::CreateReverb(uint32_t audioHandle,uint32_t channel) {
	audioHandle;
	channel;
	//XAudio2CreateReverb(&pXAPO_);

	//// EFFECT_DESCRIPTOR の作成
	//XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	//descriptor.InitialState = true; // 最初から有効状態
	//descriptor.OutputChannels = 2; // 2ch のエフェクトだよ
	//descriptor.pEffect = pXAPO_; // エフェクト本体
	//// EFFECT_CHAIN の作成
	//XAUDIO2_EFFECT_CHAIN chain;
	//chain.EffectCount = 1; // 挿すのは 1 個ですよ
	//chain.pEffectDescriptors = &descriptor; // さっきの構造体を指示
	//// ボイスに EFFECT_CHAIN を挿す
	//audioInformation_[audioHandle].pSourceVoice_->SetEffectChain(&chain);

	//// EFFECT_CHAIN の作成
	//XAUDIO2_EFFECT_CHAIN chain;
	//chain.EffectCount = 1;
	//chain.pEffectDescriptors = &descriptor;

	//// ボイスに EFFECT_CHAIN を挿す
	//Audio::GetInstance()->submixVoice_[channel]->SetEffectChain(&chain);

	//pXAPO_->Release();
}


//エフェクトの効果を無効にする
void Audio::OffEffect(uint32_t audioHandle) {
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->DisableEffect(0);
	assert(SUCCEEDED(hr));
}

//エフェクトの効果を有効にする
void Audio::OnEffect(uint32_t audioHandle) {
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->EnableEffect(0);
	assert(SUCCEEDED(hr));
}



#pragma endregion


//音声データの開放
//後ろにあるReleaseで使っているよ
void Audio::SoundUnload(uint32_t soundDataHandle) {
	//バッファのメモリを解放
	delete[] Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.pBuffer;
	Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.pBuffer = 0;
	Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.bufferSize = 0;
	Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.wfex = {};

}

//解放
void Audio::Release() {
	//解放
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		//中身が入っていたらしっかり解放
		if (audioInformation_[i].pSourceReader_ != nullptr) {
			audioInformation_[i].pSourceReader_->Release();
		}
		if (audioInformation_[i].pSourceVoice_ != nullptr) {
			audioInformation_[i].pSourceVoice_->DestroyVoice();
		}
	}


	//XAudio2解放
	xAudio2_.Reset();

	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		SoundUnload(i);
	}
	HRESULT hr{};
	hr=MFShutdown();
	assert(SUCCEEDED(hr));
}
