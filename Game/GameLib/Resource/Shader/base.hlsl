
// 頂点シェーダーの出力パラメータ
struct VS_OUT
{
   float4 pos   : SV_POSITION;
   float4 color : COLOR0;
};

// 頂点シェーダー
VS_OUT VS_Main( VS_IN In )
{
   VS_OUT Out;

   Out.pos = mul( float4( In.pos, 1 ), g_matWVP );
   Out.color = In.color;

   return Out;
}

// ピクセルシェーダ
float4 PS_Main( VS_OUT In ) : SV_TARGET
{
   return In.color;
}
