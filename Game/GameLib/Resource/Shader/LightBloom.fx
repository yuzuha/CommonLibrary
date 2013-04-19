// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------
float	m_Bloom = 1.0f;	///< �����o���P�x�̋��E

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture SourceTex;
sampler SourceSampler = sampler_state
{
	Texture		= (SourceTex);
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
	float4 Pos		: POSITION;
	float2 Tex		: TEXCOORD0;
};

// -------------------------------------------------------------
// Pass0 : ���_�V�F�[�_�[ �P�x�e�N�X�`���쐬
// -------------------------------------------------------------
VS_OUT VS_0(
				float4 Position	: POSITION,
				float2 Tex		: TEXCOORD0 )
{
	VS_OUT Out		= (VS_OUT)0;

	Out.Pos			= Position;
	Out.Tex			= Tex;

	return Out;
}

// -------------------------------------------------------------
// Pass0 : �s�N�Z���V�F�[�_�[ �P�x�e�N�X�`���쐬
// -------------------------------------------------------------
float4 PS_0( VS_OUT In) : COLOR
{
	// �P�x = r * 0.298912f + g * 0.586611f + b * 0.114478f
	float3 color	= tex2D( SourceSampler, In.Tex );
	float4 rtn		= (((0.298912f*color.x + 0.586611f*color.y + 0.114478f*color.z) < m_Bloom) ? float4(0,0,0,0) : tex2D( SourceSampler, In.Tex ));
	return rtn;
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	//--------------------
	// �P�x�e�N�X�`���̐���
	//--------------------
	pass p0
	{
		VertexShader	= compile vs_2_0 VS_0();
		PixelShader		= compile ps_2_0 PS_0();
	}

}