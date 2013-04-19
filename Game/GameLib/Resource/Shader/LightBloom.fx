// -------------------------------------------------------------
// グローバル変数
// -------------------------------------------------------------
float	m_Bloom = 1.0f;	///< 抜き出す輝度の境界

// -------------------------------------------------------------
// テクスチャ
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
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUT
{
	float4 Pos		: POSITION;
	float2 Tex		: TEXCOORD0;
};

// -------------------------------------------------------------
// Pass0 : 頂点シェーダー 輝度テクスチャ作成
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
// Pass0 : ピクセルシェーダー 輝度テクスチャ作成
// -------------------------------------------------------------
float4 PS_0( VS_OUT In) : COLOR
{
	// 輝度 = r * 0.298912f + g * 0.586611f + b * 0.114478f
	float3 color	= tex2D( SourceSampler, In.Tex );
	float4 rtn		= (((0.298912f*color.x + 0.586611f*color.y + 0.114478f*color.z) < m_Bloom) ? float4(0,0,0,0) : tex2D( SourceSampler, In.Tex ));
	return rtn;
}

// -------------------------------------------------------------
// テクニック
// -------------------------------------------------------------
technique TShader
{
	//--------------------
	// 輝度テクスチャの生成
	//--------------------
	pass p0
	{
		VertexShader	= compile vs_2_0 VS_0();
		PixelShader		= compile ps_2_0 PS_0();
	}

}