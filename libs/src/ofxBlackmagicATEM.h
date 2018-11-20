#pragma once
#define interface  struct
#include "BMDSwitcherAPI_h.h"
#include "ofMain.h"
#include "ATEMInput.h"

class ofxBlackmagicATEM
{
public:
	enum INPUT_ID
	{
		NO1, NO2, NO3, NO4, NO5, NO6, NO7, NO8
	};

	ofxBlackmagicATEM();
	~ofxBlackmagicATEM();
	void setup(string ipAddress);
	void update();
	void changePgOut(ofxBlackmagicATEM::INPUT_ID inputID);
private:

	IBMDSwitcherDiscovery * switcherDiscovery;
	IBMDSwitcher*				mSwitcher;
	IBMDSwitcherMixEffectBlock*	mMixEffectBlock;
	vector<ATEMInput> inputs;


	void connect(string ipAddress);
	void disconnect();

	BSTR ConvertMBSToBSTR(const std::string& str)
	{
		int wslen = ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
			str.data(), str.length(),
			NULL, 0);

		BSTR wsdata = ::SysAllocStringLen(NULL, wslen);
		::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
			str.data(), str.length(),
			wsdata, wslen);
		return wsdata;
	}

	string ConvertBSTRToMBS(BSTR bstr)
	{
		int wslen = ::SysStringLen(bstr);
		return ConvertWCSToMBS((wchar_t*)bstr, wslen);
	}

	std::string ConvertWCSToMBS(const wchar_t* pstr, long wslen)
	{
		int len = ::WideCharToMultiByte(CP_ACP, 0, pstr, wslen, NULL, 0, NULL, NULL);

		std::string dblstr(len, '\0');
		len = ::WideCharToMultiByte(CP_ACP, 0 /* no flags */,
			pstr, wslen /* not necessary NULL-terminated */,
			&dblstr[0], len,
			NULL, NULL /* no default char */);

		return dblstr;
	}


};


