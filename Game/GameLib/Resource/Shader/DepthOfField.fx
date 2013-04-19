// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------
float4x4	m_WV;					///< ���[���h * �r���[ �s��
float4x4	m_WVP;					///< ���[���h * �r���[ * �ˉe�ϊ� �s��
float		m_Focus = 1;			///< �œ_����
float		m_LensFStop = 1;		///< �J��F�l
float		m_FarClip = 20;			///< �ő�N���b�v�ʂ܂ł̋���
float		m_TexWidth = 1024;		///< �e�N�X�`���̃T�C�Y
float		m_TexHeight = 1024;		///< �e�N�X�`���̃T�C�Y
float		m_BlurPower = 10;		///< �ڂ����
float4x4	m_Bias;					///< 

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture SceneTex;
sampler SceneSampler = sampler_state
{
	Texture		= (SceneTex);
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= NONE;
	AddressU	= Clamp;
	AddressV	= Clamp;
//	AddressU	= Wrap;
//	AddressV	= Wrap;
};
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture		= (DepthTex);
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= NONE;
	AddressU	= Clamp;
	AddressV	= Clamp;
};

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUT
{
	float4 Pos	: POSITION;
	float4 Col	: COLOR0;
	float2 TC	: TEXCOORD0;
};

// -------------------------------------------------------------
// Pass0 : ���_�V�F�[�_�[ �[�x�e�N�X�`���쐬
// -------------------------------------------------------------
VS_OUT VS_0(
				float4 Position	: POSITION,
				float2 TC		: TEXCOORD0 )
{
	VS_OUT Out		= (VS_OUT)0;

	Out.Pos			= mul( Position, m_WVP ); 
	float4 Pos		= mul( Position, m_WV );

	float Length	= length( Pos );

	if( Length < m_Focus - m_LensFStop / 2 )	//�œ_�̈���O��
	{
		Length		= abs( m_Focus - Length );
	}
	else if( Length > m_Focus + m_LensFStop / 2 )	//�œ_�̈�����
	{
		Length		= abs( Length - m_Focus );
	}
	else	//�œ_�̈���i�u���Ȃ��j
	{
		Length = 0;
	}
	Out.Col.r		= Length / m_FarClip;

	return Out;
}

// -------------------------------------------------------------
// Pass1 : ���_�V�F�[�_�[ �ڂ���
// -------------------------------------------------------------
VS_OUT VS_1(
			float4 Position	: POSITION,
			float2 TC		: TEXCOORD0 )
{
	VS_OUT Out	= (VS_OUT)0;

	Out.Pos		= Position;
	Out.TC		= TC;

	return Out;
}

// -------------------------------------------------------------
// Pass0 : �s�N�Z���V�F�[�_�[ �[�x�e�N�X�`���쐬
// -------------------------------------------------------------
float4 PS_0( VS_OUT In) : COLOR
{
	return In.Col;
}

// -------------------------------------------------------------
// Pass1 : �s�N�Z���V�F�[�_�[ �ڂ���
// -------------------------------------------------------------
float4 PS_1( VS_OUT In) : COLOR
{
	float4 LengthOnTex	= tex2D( DepthSampler, In.TC );
	float Length		= LengthOnTex.r;

	Length				*= m_BlurPower;

	float2 TC0,TC1,TC2,TC3;
	float DeltaH		= Length / m_TexWidth;
	float DeltaV		= Length / m_TexHeight;
	TC0					= In.TC + float2( -DeltaH, -DeltaV );
	TC1					= In.TC + float2(  DeltaH, -DeltaV );
	TC2					= In.TC + float2( -DeltaH,  DeltaV );
	TC3					= In.TC + float2(  DeltaH,  DeltaV );

	float4 Color0		= tex2D( SceneSampler, TC0 );
	float4 Color1		= tex2D( SceneSampler, TC1 );
	float4 Color2		= tex2D( SceneSampler, TC2 );
	float4 Color3		= tex2D( SceneSampler, TC3 );

	return ( Color0 + Color1 + Color2 + Color3 ) / 4.0f;

}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	//--------------------
	// �[�x�e�N�X�`���̐���
	//--------------------
	pass p0
	{
		VertexShader	= compile vs_2_0 VS_0();
		PixelShader		= compile ps_2_0 PS_0();
	}

	//--------------------
	// �ڂ���
	//--------------------
	pass p1
	{
		VertexShader	= compile vs_2_0 VS_1();
		PixelShader		= compile ps_2_0 PS_1();
	}
}