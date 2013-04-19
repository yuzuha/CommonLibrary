// -------------------------------------------------------------
// グローバル変数
// -------------------------------------------------------------
float4x4 mWorld;		// ワールド行列
float4x4 mView;			// 射影行列
float4x4 mProj;			// 投影行列
float4 vLightDir;		// ライトの方向
float4 vColor;			// ライト＊メッシュの色

// スキンメッシュ用
float4x4 matWorld[4];	// 合成用ワールド行列
int	BlendNum;			// 合成する数

// シャドウマップ用
float4x4 mLView;		// ライト 射影行列
float4x4 mLProj;		// ライト 投影行列
float4x4 mBias;			// ライト

// バンプマップ用
float4 vEyePos;			// カメラの視点

// -------------------------------------------------------------
// テクスチャ
// -------------------------------------------------------------
// シャドウマップ
texture ShadowMap;
sampler ShadowMapSamp = sampler_state
{
	Texture = <ShadowMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	
	AddressU = Clamp;
	AddressV = Clamp;
};
// -------------------------------------------------------------
// テクスチャマップ
texture DecaleMap;
sampler DecaleMapSamp = sampler_state
{
	Texture = <DecaleMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Wrap;
	AddressV = Wrap;
//	AddressU = Clamp;
//	AddressV = Clamp;
};
// -------------------------------------------------------------
// 法線マップ
texture NormalMap;
sampler NormalSamp = sampler_state
{
    Texture = <NormalMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};
// -------------------------------------------------------------
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float4 Diffuse		: COLOR0;
	float4 Ambient		: COLOR1;
//	float4 Diffuse2		: COLOR2;
	float4 ShadowMapUV	: TEXCOORD0;
	float4 Depth		: TEXCOORD1;	// 比較のための深度値
	float2 Texture		: TEXCOORD2;	// デカールテクスチャ
    float3 L			: TEXCOORD3;	// ライトベクトル
    float3 E			: TEXCOORD4;	// 視線ベクトル
};

// -------------------------------------------------------------
// Pass0 : 頂点シェーダー シャドウマップ 通常メッシュ
// -------------------------------------------------------------
VS_OUTPUT VS_0_1
	( float4 Pos	: POSITION			// モデルの頂点
	, float3 Normal	: NORMAL )			// モデルの法線
{
    VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ
    
    // 位置座標
	Out.Pos =  mul( Pos, mWorld );
	Out.Pos =  mul( Out.Pos, mLView );
	Out.Pos =  mul( Out.Pos, mLProj );
    
    // カメラ座標系での深度をテクスチャに入れる
    Out.ShadowMapUV =  Out.Pos;

    return Out;
}

// -------------------------------------------------------------
// Pass1 : 頂点シェーダー シャドウマップ スキンメッシュ
// -------------------------------------------------------------
VS_OUTPUT VS_0_2
	( float4 Pos	: POSITION			// モデルの頂点
	, float4 Blend	: BLENDWEIGHT		// 重み
	, float3 Normal	: NORMAL )			// モデルの法線
{
    VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ
    
    // 位置座標
	float w[4] = (float[4])Blend;		//重み
	float4x4 comb = (float4x4)0;		//合成用
	float LastBlendWeight = 0;

	//ワールド行列の合成
	for( int i=0;i<BlendNum-1;i++ ){
		LastBlendWeight += w[i];
		comb += matWorld[i] * w[i];		
	}
	comb += matWorld[BlendNum -1] * ( 1.0f - LastBlendWeight);

	Out.Pos = mul( Pos, comb );
	Out.Pos = mul( Out.Pos, mLView );
	Out.Pos = mul( Out.Pos, mLProj );
    
    // カメラ座標系での深度をテクスチャに入れる
    Out.ShadowMapUV =  Out.Pos;

    return Out;
}

// -------------------------------------------------------------
// Pass2 : 頂点シェーダー 通常メッシュ
// -------------------------------------------------------------
VS_OUTPUT VS_1
	( float4 Pos		: POSITION		// ローカル位置座標
	, float3 Normal		: NORMAL 		// 法線ベクトル
	, float3 Tangent	: TANGENT0		// 接ベクトル
	, float2 Texture	: TEXCOORD )	// テクスチャ
{
	VS_OUTPUT Out	= (VS_OUTPUT)0;		// 出力データ
	
	// 座標変換
	Out.Pos			= mul( Pos, mWorld );
	Out.Pos			= mul( Out.Pos, mView );
	Out.Pos			= mul( Out.Pos, mProj );

	// 色
	float3	LD		= vLightDir.xyz;
	float	Dot		= dot(LD, Normal);
	Dot				= Dot * 0.5 + 0.5f;	// 1 ～ 0の間にする
//	Out.Diffuse2	= vColor;										// 原色
	Out.Diffuse		= vColor * Dot;									// 拡散色
	Out.Ambient		= vColor * 0.3f;								// 環境色
	Out.Ambient.a	= vColor.a;									// 環境色
	
	// シャドウマップ
	Out.ShadowMapUV = mul( Pos, mWorld );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLView );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLProj );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mBias );

	// 比較のための深度値
	Out.Depth		= mul( Pos, mWorld );
	Out.Depth		= mul( Out.Depth, mLView );
	Out.Depth		= mul( Out.Depth, mLProj );

	// デカールテクスチャ
	Out.Texture		= Texture;
	
	// ------------------------------
	// バンプ用
	// ------------------------------
	// 座標系の変換基底
	float3 N		= Normal;
	float3 T		= Tangent;
	float3 B		= cross(N,T);

	// 鏡面反射用のベクトル
	float3 E		= vEyePos - Pos.xyz;	// 視線ベクトル
	Out.E.x			= dot(E,T);
	Out.E.y			= dot(E,B);
	Out.E.z			= dot(E,N);

	float3 L		= -vLightDir.xyz;		// ライトベクトル
	Out.L.x			= dot(L,T);
	Out.L.y			= dot(L,B);
	Out.L.z			= dot(L,N);
	
	return Out;
}

// -------------------------------------------------------------
// Pass4 : 頂点シェーダー スキンメッシュ
// -------------------------------------------------------------
VS_OUTPUT VS_2
	( float4 Pos		: POSITION		// 座標
	, float4 Blend		: BLENDWEIGHT	// 重み
	, float3 Normal		: NORMAL		// 法線
	, float3 Tangent	: TANGENT0		// 接ベクトル
	, float2 Texture	: TEXCOORD )	// テクスチャ
{
	VS_OUTPUT Out	= (VS_OUTPUT)0;				// 出力データ

	float w[4]		= (float[4])Blend;		//重み
	float4x4 comb	= (float4x4)0;		//合成用
	float LastBlendWeight = 0;

	//ワールド行列の合成
	for( int i=0;i<BlendNum-1;i++ ){
		LastBlendWeight += w[i];
		comb += matWorld[i] * w[i];		
	}
	comb += matWorld[BlendNum -1] * ( 1.0f - LastBlendWeight);

	// 座標変換
	Out.Pos = mul( Pos, comb );
	Out.Pos = mul( Out.Pos, mView );
	Out.Pos = mul( Out.Pos, mProj );

	// 色
	float3	LD	= vLightDir.xyz;
	float	Dot = dot(LD, Normal);
	Dot			= Dot * 0.5 + 0.5f;	// 1 ～ 0の間にする
//	Out.Diffuse2 = vColor;										// 原色
	Out.Diffuse = vColor * Dot;									// 拡散色
	Out.Ambient = vColor * 0.3f;								// 環境色
	Out.Ambient.a = vColor.a;									// 環境色
	
	// シャドウマップ
	Out.ShadowMapUV = mul( Pos, comb );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLView );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLProj );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mBias );

	// 比較のための深度値
	Out.Depth = mul( Pos, comb );
	Out.Depth = mul( Out.Depth, mLView );
	Out.Depth = mul( Out.Depth, mLProj );

	// デカールテクスチャ
	Out.Texture = Texture;
	
	// ------------------------------
	// バンプ用
	// ------------------------------
	// 座標系の変換基底
	float3 N = Normal;
	float3 T = Tangent;
	float3 B = cross(N,T);

	// 鏡面反射用のベクトル
	float3 E = vEyePos - Pos.xyz;	// 視線ベクトル
	Out.E.x = dot(E,T);
	Out.E.y = dot(E,B);
	Out.E.z = dot(E,N);

	float3 L = -vLightDir.xyz;		// ライトベクトル
	Out.L.x = dot(L,T);
	Out.L.y = dot(L,B);
	Out.L.z = dot(L,N);
	
	return Out;
}

// -------------------------------------------------------------
// Pass0,1 : ピクセルシェーダー シャドウマップ
// -------------------------------------------------------------
float4 PS_0(VS_OUTPUT In) : COLOR
{   

	float color = In.ShadowMapUV.z / In.ShadowMapUV.w;
	return float4( color, color*color, 0, 1 );
	
}

// -------------------------------------------------------------
// Pass2,7 : ピクセルシェーダー(テクスチャ無)(ライト有)
// -------------------------------------------------------------
float4 PS_1_1(VS_OUTPUT In) : COLOR
{   

	float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
    
	Color = In.Ambient
		 + ((shadow * In.Depth.w < In.Depth.z-0.003f) ? 0 : In.Diffuse);
    Color.a = In.Ambient.a;
	
	return Color;

}

// -------------------------------------------------------------
// Pass3,8 : ピクセルシェーダー(テクスチャ有)(ライト有)
// -------------------------------------------------------------
float4 PS_1_2(VS_OUTPUT In) : COLOR
{   

    float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
	float4 decale = tex2D( DecaleMapSamp, In.Texture );
    
    Color = In.Ambient
		 + ((shadow * In.Depth.w < In.Depth.z-0.008f) ? 0.2f : In.Diffuse);
    Color.a = In.Ambient.a;

	return Color * decale;

}

// -------------------------------------------------------------
// Pass4,9 : ピクセルシェーダー(テクスチャ無)(ライト無)
// -------------------------------------------------------------
float4 PS_1_3(VS_OUTPUT In) : COLOR
{   

	float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
    
	Color = In.Ambient
//		 + ((shadow * In.Depth.w < In.Depth.z-0.003f) ? 0 : In.Diffuse2);
		 + ((shadow * In.Depth.w < In.Depth.z-0.003f) ? 0 : In.Diffuse);
    Color.a = In.Ambient.a;
	
	return Color;

}

// -------------------------------------------------------------
// Pass5,10 : ピクセルシェーダー(テクスチャ有)(ライト無)
// -------------------------------------------------------------
float4 PS_1_4(VS_OUTPUT In) : COLOR
{   

    float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
	float4 decale = tex2D( DecaleMapSamp, In.Texture );
    
    Color = In.Ambient
//		 + ((shadow * In.Depth.w < In.Depth.z-0.003f) ? 0 : In.Diffuse2);
		 + ((shadow * In.Depth.w < In.Depth.z-0.003f) ? 0 : In.Diffuse);
    Color.a = In.Ambient.a;

	return Color * decale;

}

// -------------------------------------------------------------
// Pass6,11 : ピクセルシェーダー(バンプマップ)
// -------------------------------------------------------------
float4 PS_1_5(VS_OUTPUT In) : COLOR
{   

    float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
	float4 decale = tex2D( DecaleMapSamp, In.Texture );
    
    Color = In.Ambient
		 + ((shadow * In.Depth.w < In.Depth.z-0.003f) ? 0 : In.Diffuse);
    Color.a = In.Ambient.a;

	return Color * decale;

	/*
	float3 N = 2.0f*tex2D( NormalSamp, In.Tex ).xyz-1.0;// 法線マップからの法線
	float3 L = normalize(In.L);						// ライトベクトル
	float3 R = reflect(-normalize(In.E), N);		// 反射ベクトル
	float amb = -vLightDir.w;						// 環境光の強さ
	
	return In.Color * tex2D( DecaleSamp, In.Tex )	// 拡散光と環境光には、
			   * (max(0, dot(N, L))+amb)			// 頂点色とテクスチャの色を合成する
			 + 0.3f * pow(max(0,dot(R, L)), 8);		// Phong 鏡面反射光
	*/

}

// -------------------------------------------------------------
// テクニック
// -------------------------------------------------------------
technique TShader
{
	
	//--------------------
	// シャドウマップ
	//--------------------
    pass P0	// シャドウマップ・通常メッシュ
    {
        VertexShader = compile vs_3_0 VS_0_1();
        PixelShader  = compile ps_3_0 PS_0();
    }
    pass P1	// シャドウマップ・スキンメッシュ
    {
        VertexShader = compile vs_3_0 VS_0_2();
        PixelShader  = compile ps_3_0 PS_0();
    }

	//--------------------
	// 通常メッシュ
	//--------------------
    pass P2	// 通常メッシュ(テクスチャ無)(ライト有)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_1();
    }
    pass P3	// 通常メッシュ(テクスチャ有)(ライト有)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_2();
    }
    pass P4	// 通常メッシュ(テクスチャ無)(ライト無)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_3();
    }
    pass P5	// 通常メッシュ(テクスチャ有)(ライト無)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_4();
    }
    pass P6	// 通常メッシュ(バンプマップ)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_5();
    }

	//--------------------
	// スキンメッシュ
	//--------------------
    pass P7	// スキンメッシュ(テクスチャ無)(ライト有)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_1();
    }
    pass P8	// スキンメッシュ(テクスチャ有)(ライト有)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_2();
    }
    pass P9	// スキンメッシュ(テクスチャ無)(ライト無)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_3();
    }
    pass P10	// スキンメッシュ(テクスチャ有)(ライト無)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_4();
    }
    pass P11	// スキンメッシュ(バンプマップ)
    {
		VertexShader = compile vs_2_0 VS_2();
		PixelShader  = compile ps_2_0 PS_1_5();
    }

}
