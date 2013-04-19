// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------
float	m_TexWidth;			///< �e�N�X�`���T�C�YX
float	m_TexHeight;		///< �e�N�X�`���T�C�YY
float	m_BlurPower	= 1.0f;	///< �ڂ����̋���
float	m_Alpha		= 1.0f;	///< �`�掞�̃A���t�@�l

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture SourceTex;
sampler SourceSampler = sampler_state
{
	Texture		= <SourceTex>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= NONE;

	AddressU	= Clamp;
	AddressV	= Clamp;
};
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

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUT
{
	float4 Pos	: POSITION;
	float2 Tex	: TEXCOORD0;
};

// -------------------------------------------------------------
// Pass0,1 : ���_�V�F�[�_�[ �ڂ���
// -------------------------------------------------------------
VS_OUT VS_0(
				float4 Position	: POSITION,
				float2 Texture	: TEXCOORD0 )
{
	VS_OUT Out		= (VS_OUT)0;

	// �ʒu
//	Out.Pos			= mul( Position, m_WVP ); 
	Out.Pos			= Position; 
	Out.Tex			= Texture;

	return Out;
}

// -------------------------------------------------------------
// Pass2 : ���_�V�F�[�_�[ �`��
// -------------------------------------------------------------
VS_OUT VS_2(
				float4 Position	: POSITION,
				float2 Texture	: TEXCOORD0 )
{
	VS_OUT Out		= (VS_OUT)0;

	// �ʒu
	Out.Pos			= Position; 
	Out.Tex			= Texture;

	return Out;
}

// -------------------------------------------------------------
// Pass0 : �s�N�Z���V�F�[�_�[ �ڂ���X
// -------------------------------------------------------------
float4 PS_0( VS_OUT In) : COLOR
{
	// �ڂ���
	float2 Tex0		= In.Tex + float2( -1.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex1		= In.Tex + float2( -2.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex2		= In.Tex + float2( -3.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex3		= In.Tex + float2( -4.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex4		= In.Tex + float2( -5.0f * m_BlurPower / m_TexWidth, 0.0f );

	float2 Tex5		= In.Tex + float2(  1.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex6		= In.Tex + float2(  2.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex7		= In.Tex + float2(  3.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex8		= In.Tex + float2(  4.0f * m_BlurPower / m_TexWidth, 0.0f );
	float2 Tex9		= In.Tex + float2(  5.0f * m_BlurPower / m_TexWidth, 0.0f );

	float4 p0		= tex2D( SourceSampler, In.Tex ) * 0.20f;

	float4 p1		= tex2D( SourceSampler, Tex0 ) * 0.12f;
	float4 p2		= tex2D( SourceSampler, Tex1 ) * 0.10f;
	float4 p3		= tex2D( SourceSampler, Tex2 ) * 0.08f;
	float4 p4		= tex2D( SourceSampler, Tex3 ) * 0.06f;
	float4 p5		= tex2D( SourceSampler, Tex4 ) * 0.04f;

	float4 p6		= tex2D( SourceSampler, Tex5 ) * 0.12f;
	float4 p7		= tex2D( SourceSampler, Tex6 ) * 0.10f;
	float4 p8		= tex2D( SourceSampler, Tex7 ) * 0.08f;
	float4 p9		= tex2D( SourceSampler, Tex8 ) * 0.06f;
	float4 p10		= tex2D( SourceSampler, Tex9 ) * 0.04f;

	return p0 + p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10;
}

// -------------------------------------------------------------
// Pass1 : �s�N�Z���V�F�[�_�[ �ڂ���Y
// -------------------------------------------------------------
float4 PS_1( VS_OUT In) : COLOR
{
	// �ڂ���
	float2 Tex0		= In.Tex + float2( 0.0f, -1.0f * m_BlurPower / m_TexHeight );
	float2 Tex1		= In.Tex + float2( 0.0f, -2.0f * m_BlurPower / m_TexHeight );
	float2 Tex2		= In.Tex + float2( 0.0f, -3.0f * m_BlurPower / m_TexHeight );
	float2 Tex3		= In.Tex + float2( 0.0f, -4.0f * m_BlurPower / m_TexHeight );
	float2 Tex4		= In.Tex + float2( 0.0f, -5.0f * m_BlurPower / m_TexHeight );

	float2 Tex5		= In.Tex + float2( 0.0f,  1.0f * m_BlurPower / m_TexHeight );
	float2 Tex6		= In.Tex + float2( 0.0f,  2.0f * m_BlurPower / m_TexHeight );
	float2 Tex7		= In.Tex + float2( 0.0f,  3.0f * m_BlurPower / m_TexHeight );
	float2 Tex8		= In.Tex + float2( 0.0f,  4.0f * m_BlurPower / m_TexHeight );
	float2 Tex9		= In.Tex + float2( 0.0f,  5.0f * m_BlurPower / m_TexHeight );

	float4 p0		= tex2D( SourceSampler, In.Tex ) * 0.20f;

	float4 p1		= tex2D( SourceSampler, Tex0 ) * 0.12f;
	float4 p2		= tex2D( SourceSampler, Tex1 ) * 0.10f;
	float4 p3		= tex2D( SourceSampler, Tex2 ) * 0.08f;
	float4 p4		= tex2D( SourceSampler, Tex3 ) * 0.06f;
	float4 p5		= tex2D( SourceSampler, Tex4 ) * 0.04f;

	float4 p6		= tex2D( SourceSampler, Tex5 ) * 0.12f;
	float4 p7		= tex2D( SourceSampler, Tex6 ) * 0.10f;
	float4 p8		= tex2D( SourceSampler, Tex7 ) * 0.08f;
	float4 p9		= tex2D( SourceSampler, Tex8 ) * 0.06f;
	float4 p10		= tex2D( SourceSampler, Tex9 ) * 0.04f;

	return p0 + p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10;
}

// -------------------------------------------------------------
// Pass2 : �s�N�Z���V�F�[�_�[ �`��
// -------------------------------------------------------------
float4 PS_2( VS_OUT In) : COLOR
{
	float4 color = tex2D( SceneSampler, In.Tex );
	color.a = m_Alpha;
	return color;
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	//--------------------
	// �ڂ���X
	//--------------------
	pass p0
	{
		VertexShader	= compile vs_2_0 VS_0();
		PixelShader		= compile ps_2_0 PS_0();
	}

	//--------------------
	// �ڂ���Y
	//--------------------
	pass p1
	{
		VertexShader	= compile vs_2_0 VS_0();
		PixelShader		= compile ps_2_0 PS_1();
	}

	//--------------------
	// �`��
	//--------------------
	pass p2
	{
		VertexShader	= compile vs_2_0 VS_2();
		PixelShader		= compile ps_2_0 PS_2();
	}
}