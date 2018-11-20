#include "ofxBlackmagicATEM.h"

ofxBlackmagicATEM::ofxBlackmagicATEM()
{
	switcherDiscovery = NULL;
	mSwitcher = NULL;

}


ofxBlackmagicATEM::~ofxBlackmagicATEM()
{
	disconnect();
}

void ofxBlackmagicATEM::setup(string ipAddress)
{
	connect(ipAddress);
}

void ofxBlackmagicATEM::update()
{

}


void ofxBlackmagicATEM::changePgOut(ofxBlackmagicATEM::INPUT_ID inputID)
{
	if (mMixEffectBlock)
	{
		mMixEffectBlock->SetInt(bmdSwitcherMixEffectBlockPropertyIdProgramInput, inputs[inputID + 1].inputId);
	}
	else
	{
		ofLogWarning() << "switcher is not created";
	}
}

void ofxBlackmagicATEM::connect(string ipAddress)
{
	if (FAILED(CoInitialize(NULL)))
	{
		ofLogError() << "Could not create initialize Switcher.";

	}

	if(FAILED(CoCreateInstance(CLSID_CBMDSwitcherDiscovery, NULL, CLSCTX_ALL,
		IID_IBMDSwitcherDiscovery, (void**)&switcherDiscovery)))
	{
		ofLogError() << "Could not create Switcher Discovery Instance.ATEM Switcher Software may not be installed.";
	}

	BMDSwitcherConnectToFailure	failReason;
	BSTR bstr_ = ConvertMBSToBSTR(ipAddress);
	HRESULT hr = switcherDiscovery->ConnectTo(bstr_, &mSwitcher, &failReason);
	
	SysFreeString(bstr_);
	if (SUCCEEDED(hr))
	{
		ofLog() << "success!!!";
	}
	else
	{
		switch (failReason)
		{
		case bmdSwitcherConnectToFailureNoResponse:
			ofLogError() << "No response from Switcher";
			break;
		case bmdSwitcherConnectToFailureIncompatibleFirmware:
			ofLogError() << "Switcher has incompatible firmware";
			break;
		default:
			ofLogError() << "Connection failed for unknown reason";
			break;
		}
	}

	// Create an InputMonitor for each input so we can catch any changes to input names
	IBMDSwitcherInputIterator* inputIterator = NULL;
	hr = mSwitcher->CreateIterator(IID_IBMDSwitcherInputIterator, (void**)&inputIterator);
	if (SUCCEEDED(hr))
	{
		IBMDSwitcherInput* input = NULL;

		// For every input, install a callback to monitor property changes on the input
		while (S_OK == inputIterator->Next(&input))
		{
			BMDSwitcherInputId input_id;
			BSTR longName;
			input->GetLongName(&longName);
			input->GetInputId(&input_id);
			string longnamestr = ConvertBSTRToMBS(longName);
			inputs.push_back(ATEMInput(input_id, longnamestr));
		}
		inputIterator->Release();
		inputIterator = NULL;
	}

	IBMDSwitcherMixEffectBlockIterator* iterator = NULL;
	hr = mSwitcher->CreateIterator(IID_IBMDSwitcherMixEffectBlockIterator, (void**)&iterator);
	if (FAILED(hr))
	{
		ofLogError() << "could not get iterator";
	}
	if (S_OK != iterator->Next(&mMixEffectBlock))
	{
		ofLogError() << "could not get the first IBMDSwitcherMixEffectBlock";
	}
	if (iterator)
	{
		iterator->Release();
	}

}

void ofxBlackmagicATEM::disconnect()
{
	ofLog() << "disconnect";
	if (mSwitcher)
	{
		/*mSwitcher->RemoveCallback(mSwitcherMonitor);*/
		mSwitcher->Release();
		mSwitcher = NULL;
	}
}
