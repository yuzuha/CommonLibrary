// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------
float4x4 mWorld;		// ���[���h�s��
float4x4 mView;			// �ˉe�s��
float4x4 mProj;			// ���e�s��
float4 vLightDir;		// ���C�g�̕���
float4 vColor;			// ���C�g�����b�V���̐F

// �X�L�����b�V���p
float4x4 matWorld[4];	// �����p���[���h�s��
int	BlendNum;			// �������鐔

// �V���h�E�}�b�v�p
float4x4 mLView;		// ���C�g �ˉe�s��
float4x4 mLProj;		// ���C�g ���e�s��
float4x4 mBias;			// ���C�g

// �o���v�}�b�v�p
float4 vEyePos;			// �J�����̎��_

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
// �V���h�E�}�b�v
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
// �e�N�X�`���}�b�v
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
// �@���}�b�v
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
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float4 Diffuse		: COLOR0;
	float4 Ambient		: COLOR1;
//	float4 Diffuse2		: COLOR2;
	float4 ShadowMapUV	: TEXCOORD0;
	float4 Depth		: TEXCOORD1;	// ��r�̂��߂̐[�x�l
	float2 Texture		: TEXCOORD2;	// �f�J�[���e�N�X�`��
    float3 L			: TEXCOORD3;	// ���C�g�x�N�g��
    float3 E			: TEXCOORD4;	// �����x�N�g��
};

// -------------------------------------------------------------
// Pass0 : ���_�V�F�[�_�[ �V���h�E�}�b�v �ʏ탁�b�V��
// -------------------------------------------------------------
VS_OUTPUT VS_0_1
	( float4 Pos	: POSITION			// ���f���̒��_
	, float3 Normal	: NORMAL )			// ���f���̖@��
{
    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
    
    // �ʒu���W
	Out.Pos =  mul( Pos, mWorld );
	Out.Pos =  mul( Out.Pos, mLView );
	Out.Pos =  mul( Out.Pos, mLProj );
    
    // �J�������W�n�ł̐[�x���e�N�X�`���ɓ����
    Out.ShadowMapUV =  Out.Pos;

    return Out;
}

// -------------------------------------------------------------
// Pass1 : ���_�V�F�[�_�[ �V���h�E�}�b�v �X�L�����b�V��
// -------------------------------------------------------------
VS_OUTPUT VS_0_2
	( float4 Pos	: POSITION			// ���f���̒��_
	, float4 Blend	: BLENDWEIGHT		// �d��
	, float3 Normal	: NORMAL )			// ���f���̖@��
{
    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
    
    // �ʒu���W
	float w[4] = (float[4])Blend;		//�d��
	float4x4 comb = (float4x4)0;		//�����p
	float LastBlendWeight = 0;

	//���[���h�s��̍���
	for( int i=0;i<BlendNum-1;i++ ){
		LastBlendWeight += w[i];
		comb += matWorld[i] * w[i];		
	}
	comb += matWorld[BlendNum -1] * ( 1.0f - LastBlendWeight);

	Out.Pos = mul( Pos, comb );
	Out.Pos = mul( Out.Pos, mLView );
	Out.Pos = mul( Out.Pos, mLProj );
    
    // �J�������W�n�ł̐[�x���e�N�X�`���ɓ����
    Out.ShadowMapUV =  Out.Pos;

    return Out;
}

// -------------------------------------------------------------
// Pass2 : ���_�V�F�[�_�[ �ʏ탁�b�V��
// -------------------------------------------------------------
VS_OUTPUT VS_1
	( float4 Pos		: POSITION		// ���[�J���ʒu���W
	, float3 Normal		: NORMAL 		// �@���x�N�g��
	, float3 Tangent	: TANGENT0		// �ڃx�N�g��
	, float2 Texture	: TEXCOORD )	// �e�N�X�`��
{
	VS_OUTPUT Out	= (VS_OUTPUT)0;		// �o�̓f�[�^
	
	// ���W�ϊ�
	Out.Pos			= mul( Pos, mWorld );
	Out.Pos			= mul( Out.Pos, mView );
	Out.Pos			= mul( Out.Pos, mProj );

	// �F
	float3	LD		= vLightDir.xyz;
	float	Dot		= dot(LD, Normal);
	Dot				= Dot * 0.5 + 0.5f;	// 1 �` 0�̊Ԃɂ���
//	Out.Diffuse2	= vColor;										// ���F
	Out.Diffuse		= vColor * Dot;									// �g�U�F
	Out.Ambient		= vColor * 0.3f;								// ���F
	Out.Ambient.a	= vColor.a;									// ���F
	
	// �V���h�E�}�b�v
	Out.ShadowMapUV = mul( Pos, mWorld );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLView );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLProj );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mBias );

	// ��r�̂��߂̐[�x�l
	Out.Depth		= mul( Pos, mWorld );
	Out.Depth		= mul( Out.Depth, mLView );
	Out.Depth		= mul( Out.Depth, mLProj );

	// �f�J�[���e�N�X�`��
	Out.Texture		= Texture;
	
	// ------------------------------
	// �o���v�p
	// ------------------------------
	// ���W�n�̕ϊ����
	float3 N		= Normal;
	float3 T		= Tangent;
	float3 B		= cross(N,T);

	// ���ʔ��˗p�̃x�N�g��
	float3 E		= vEyePos - Pos.xyz;	// �����x�N�g��
	Out.E.x			= dot(E,T);
	Out.E.y			= dot(E,B);
	Out.E.z			= dot(E,N);

	float3 L		= -vLightDir.xyz;		// ���C�g�x�N�g��
	Out.L.x			= dot(L,T);
	Out.L.y			= dot(L,B);
	Out.L.z			= dot(L,N);
	
	return Out;
}

// -------------------------------------------------------------
// Pass4 : ���_�V�F�[�_�[ �X�L�����b�V��
// -------------------------------------------------------------
VS_OUTPUT VS_2
	( float4 Pos		: POSITION		// ���W
	, float4 Blend		: BLENDWEIGHT	// �d��
	, float3 Normal		: NORMAL		// �@��
	, float3 Tangent	: TANGENT0		// �ڃx�N�g��
	, float2 Texture	: TEXCOORD )	// �e�N�X�`��
{
	VS_OUTPUT Out	= (VS_OUTPUT)0;				// �o�̓f�[�^

	float w[4]		= (float[4])Blend;		//�d��
	float4x4 comb	= (float4x4)0;		//�����p
	float LastBlendWeight = 0;

	//���[���h�s��̍���
	for( int i=0;i<BlendNum-1;i++ ){
		LastBlendWeight += w[i];
		comb += matWorld[i] * w[i];		
	}
	comb += matWorld[BlendNum -1] * ( 1.0f - LastBlendWeight);

	// ���W�ϊ�
	Out.Pos = mul( Pos, comb );
	Out.Pos = mul( Out.Pos, mView );
	Out.Pos = mul( Out.Pos, mProj );

	// �F
	float3	LD	= vLightDir.xyz;
	float	Dot = dot(LD, Normal);
	Dot			= Dot * 0.5 + 0.5f;	// 1 �` 0�̊Ԃɂ���
//	Out.Diffuse2 = vColor;										// ���F
	Out.Diffuse = vColor * Dot;									// �g�U�F
	Out.Ambient = vColor * 0.3f;								// ���F
	Out.Ambient.a = vColor.a;									// ���F
	
	// �V���h�E�}�b�v
	Out.ShadowMapUV = mul( Pos, comb );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLView );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mLProj );
	Out.ShadowMapUV = mul( Out.ShadowMapUV, mBias );

	// ��r�̂��߂̐[�x�l
	Out.Depth = mul( Pos, comb );
	Out.Depth = mul( Out.Depth, mLView );
	Out.Depth = mul( Out.Depth, mLProj );

	// �f�J�[���e�N�X�`��
	Out.Texture = Texture;
	
	// ------------------------------
	// �o���v�p
	// ------------------------------
	// ���W�n�̕ϊ����
	float3 N = Normal;
	float3 T = Tangent;
	float3 B = cross(N,T);

	// ���ʔ��˗p�̃x�N�g��
	float3 E = vEyePos - Pos.xyz;	// �����x�N�g��
	Out.E.x = dot(E,T);
	Out.E.y = dot(E,B);
	Out.E.z = dot(E,N);

	float3 L = -vLightDir.xyz;		// ���C�g�x�N�g��
	Out.L.x = dot(L,T);
	Out.L.y = dot(L,B);
	Out.L.z = dot(L,N);
	
	return Out;
}

// -------------------------------------------------------------
// Pass0,1 : �s�N�Z���V�F�[�_�[ �V���h�E�}�b�v
// -------------------------------------------------------------
float4 PS_0(VS_OUTPUT In) : COLOR
{   

	float color = In.ShadowMapUV.z / In.ShadowMapUV.w;
	return float4( color, color*color, 0, 1 );
	
}

// -------------------------------------------------------------
// Pass2,7 : �s�N�Z���V�F�[�_�[(�e�N�X�`����)(���C�g�L)
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
// Pass3,8 : �s�N�Z���V�F�[�_�[(�e�N�X�`���L)(���C�g�L)
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
// Pass4,9 : �s�N�Z���V�F�[�_�[(�e�N�X�`����)(���C�g��)
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
// Pass5,10 : �s�N�Z���V�F�[�_�[(�e�N�X�`���L)(���C�g��)
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
// Pass6,11 : �s�N�Z���V�F�[�_�[(�o���v�}�b�v)
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
	float3 N = 2.0f*tex2D( NormalSamp, In.Tex ).xyz-1.0;// �@���}�b�v����̖@��
	float3 L = normalize(In.L);						// ���C�g�x�N�g��
	float3 R = reflect(-normalize(In.E), N);		// ���˃x�N�g��
	float amb = -vLightDir.w;						// �����̋���
	
	return In.Color * tex2D( DecaleSamp, In.Tex )	// �g�U���Ɗ����ɂ́A
			   * (max(0, dot(N, L))+amb)			// ���_�F�ƃe�N�X�`���̐F����������
			 + 0.3f * pow(max(0,dot(R, L)), 8);		// Phong ���ʔ��ˌ�
	*/

}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	
	//--------------------
	// �V���h�E�}�b�v
	//--------------------
    pass P0	// �V���h�E�}�b�v�E�ʏ탁�b�V��
    {
        VertexShader = compile vs_3_0 VS_0_1();
        PixelShader  = compile ps_3_0 PS_0();
    }
    pass P1	// �V���h�E�}�b�v�E�X�L�����b�V��
    {
        VertexShader = compile vs_3_0 VS_0_2();
        PixelShader  = compile ps_3_0 PS_0();
    }

	//--------------------
	// �ʏ탁�b�V��
	//--------------------
    pass P2	// �ʏ탁�b�V��(�e�N�X�`����)(���C�g�L)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_1();
    }
    pass P3	// �ʏ탁�b�V��(�e�N�X�`���L)(���C�g�L)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_2();
    }
    pass P4	// �ʏ탁�b�V��(�e�N�X�`����)(���C�g��)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_3();
    }
    pass P5	// �ʏ탁�b�V��(�e�N�X�`���L)(���C�g��)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_4();
    }
    pass P6	// �ʏ탁�b�V��(�o���v�}�b�v)
    {
        VertexShader = compile vs_2_0 VS_1();
        PixelShader  = compile ps_2_0 PS_1_5();
    }

	//--------------------
	// �X�L�����b�V��
	//--------------------
    pass P7	// �X�L�����b�V��(�e�N�X�`����)(���C�g�L)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_1();
    }
    pass P8	// �X�L�����b�V��(�e�N�X�`���L)(���C�g�L)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_2();
    }
    pass P9	// �X�L�����b�V��(�e�N�X�`����)(���C�g��)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_3();
    }
    pass P10	// �X�L�����b�V��(�e�N�X�`���L)(���C�g��)
    {
        VertexShader = compile vs_2_0 VS_2();
        PixelShader  = compile ps_2_0 PS_1_4();
    }
    pass P11	// �X�L�����b�V��(�o���v�}�b�v)
    {
		VertexShader = compile vs_2_0 VS_2();
		PixelShader  = compile ps_2_0 PS_1_5();
    }

}
