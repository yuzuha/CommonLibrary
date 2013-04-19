#pragma once
#include "Global.h"
using namespace std;

/**
 * �E�B���h�E���Ǘ�����N���X
 */
class Window
{
private:
	static Window			*m_pInstance;			///< ���g�̗B��̃C���X�^���X

	MSG						m_msg;					///< �E�B���h�E�v���[�W���p
	HWND					m_hWnd;					///< �E�B���h�E�n���h��
	HINSTANCE				m_hInst;				///< �C���X�^���X�n���h��
	DWORD					m_nWidth;				///< �E�B���h�E���̃N���C�A���g�̈�T�C�Y
	DWORD					m_nHeight;				///< �E�B���h�E���̃N���C�A���g�̈�T�C�Y
	float					m_fAspect;				///< �r���[�|�[�g�̃A�X�y�N�g��
	string					m_strWindowName;		///< �E�B���h�E��

	ID3D11Device			*m_pDevice;				///< �f�o�C�X
	ID3D11DeviceContext		*m_pDeviceContext;		///< �f�o�C�X�R���e�L�X�g
	IDXGISwapChain			*m_pSwapChain;			///< �X���b�v�`�F�[��
	ID3D11RenderTargetView	*m_pRenderTargetView;	///< �����_�[�^�[�Q�b�g
	ID3D11DepthStencilView	*m_pDepthStencilView;	///< �f�v�X�X�e���V���r���[
	IDXGIAdapter			*m_pAdapter;			///< �A�_�v�^�[
	D3D_FEATURE_LEVEL		m_eFeatureLevel;		///< �g�p����r�f�I�J�[�h
public:
	/**
	 * �C���X�^���X�̎擾
	 */
	static Window* GetInstance( void )
	{
		if( m_pInstance == NULL ){
			m_pInstance = new Window();
		}
		return m_pInstance;
	}

#pragma region Init
	/**
	 * ������
	 */
	static HRESULT Init( HINSTANCE _hInst )
	{
		return GetInstance()->_Init( _hInst );
	}
	/**
	 * ������
	 */
	HRESULT _Init( HINSTANCE _hInst );
#pragma endregion Init

#pragma region Cleanup
	/**
	 * �J��
	 */
	static void Cleanup( void )
	{
		GetInstance()->_Cleanup();
	}
	/**
	 * �J��
	 */
	void _Cleanup( void );
#pragma endregion Cleanup

#pragma region Destroy
	/**
	 * �j��
	 */
	static void Destroy()
	{
		GetInstance()->_Destroy();
	}
	/**
	 * �j��
	 */
	void _Destroy();
#pragma endregion Destroy

#pragma region RenderBegin
	/**
	 * �`��O
	 */
	static BOOL RenderBegin( void )
	{
		return GetInstance()->_RenderBegin();
	}
	/**
	 * �`��O
	 */
	BOOL _RenderBegin( void );
#pragma endregion RenderBegin

#pragma region RenderEnd
	/**
	 * �`���
	 */
	static void RenderEnd( void )
	{
		GetInstance()->_RenderEnd();
	}
	/**
	 * �`���
	 */
	void _RenderEnd( void );
#pragma endregion RenderEnd

#pragma region ProcessEvent
	/**
	 * �v���Z�X�C�x���g
	 */
	static BOOL ProcessEvent()
	{
		return GetInstance()->_ProcessEvent();
	}
	/**
	 * �v���Z�X�C�x���g
	 */
	BOOL _ProcessEvent();
#pragma endregion ProcessEvent

#pragma region GetDevice
	/**
	 * �f�o�C�X�̎擾
	 */
	static ID3D11Device* GetDevice()
	{
		return GetInstance()->_GetDevice();
	}
	/**
	 * �f�o�C�X�̎擾
	 */
	ID3D11Device* _GetDevice()
	{
		return m_pDevice;
	}
#pragma endregion GetDevice

#pragma region GetDeviceContext
	/**
	 * �f�o�C�X�R���e�L�X�g�̎擾
	 */
	static ID3D11DeviceContext* GetDeviceContext()
	{
		return GetInstance()->_GetDeviceContext();
	}
	/**
	 * �f�o�C�X�R���e�L�X�g�̎擾
	 */
	ID3D11DeviceContext* _GetDeviceContext()
	{
		return m_pDeviceContext;
	}
#pragma endregion GetDeviceContext

#pragma region GetSwapChain
	/**
	 * �X���b�v�`�F�[���̎擾
	 */
	static IDXGISwapChain* GetSwapChain()
	{
		return GetInstance()->_GetSwapChain();
	}
	/**
	 * �X���b�v�`�F�[���̎擾
	 */
	IDXGISwapChain* _GetSwapChain()
	{
		return m_pSwapChain;
	}
#pragma endregion GetSwapChain

#pragma region GetWindowName
	/**
	 * �E�B���h�E���̎擾
	 */
	static string GetWindowNameToString()
	{
		return GetInstance()->_GetWindowNameToString();
	}
	/**
	 * �E�B���h�E���̎擾
	 */
	string _GetWindowNameToString()
	{
		return m_strWindowName;
	}
	/**
	 * �E�B���h�E���̎擾
	 */
	static const char* GetWindowNameToChar()
	{
		return GetInstance()->_GetWindowNameToChar();
	}
	/**
	 * �E�B���h�E���̎擾
	 */
	const char* _GetWindowNameToChar()
	{
		return m_strWindowName.c_str();
	}
#pragma endregion GetWindowName

private:
	// �R���X�g���N�^
	Window( void );
	// �f�X�g���N�^
	~Window();
	// �f�t�H���g�A�_�v�^�[�̃C���^�[�t�F�[�X���쐬����
	HRESULT createAdapter();
	// �E�B���h�E�̐���
	HRESULT createWindow();
	// �f�o�C�X�̍쐬
	HRESULT createDevice();
	// �X���b�v�`�F�[���̍쐬
	HRESULT createSwapChain();
	// �^�[�Q�b�g�r���[�̍쐬
	HRESULT createTargetView();
	// �[�x�X�e���V���r���[�̍쐬
	HRESULT createDepthStencilView();
	// �r���[�|�[�g�̍쐬
	HRESULT createViewports();
	// �f�t�H���g�̃��X�^���C�U��ݒ肷��
	HRESULT setDefaultRasterize();
	// �f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ肷��
	HRESULT setDefaultDepthStencilState();
	// �E�B���h�E�v���[�W��
	static LRESULT WINAPI msgProc(HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam);
};