matrix world;
matrix view;
matrix proj;

texture OriginalRenderTexture;
sampler g_HDRSam = sampler_state
{
    texture = OriginalRenderTexture;
    MinFilter = Linear;  
    MagFilter = Linear;  
    MipFilter = Linear;  
};

texture BloomTex;
sampler g_BloomSam = sampler_state
{
    texture = BloomTex;
    MinFilter = Linear;  
    MagFilter = Linear;  
    MipFilter = Linear;  
};

texture BloomOriTex;
sampler g_BloomOriSam = sampler_state
{
    texture = BloomOriTex;
    MinFilter = Linear;  
    MagFilter = Linear;  
    MipFilter = Linear;  
};

struct VS_IN
{
	float3 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

VS_OUT VS_MAIN(/* Á¤Á¡*/VS_IN In)
{
	VS_OUT		Out;

	vector		vPosition = mul(float4(In.vPosition, 1.f), world);
	vPosition = mul(vPosition, view);
	vPosition = mul(vPosition, proj);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;


	return Out;
}

struct PS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;	
};


float4 PS_MAIN(PS_IN In) : COLOR0
{
	float4 vHDRColor = tex2D(g_HDRSam , In.vTexUV);
    float4 vBloomColor = tex2D(g_BloomSam, In.vTexUV);
    float4 vBloomOriTex = tex2D(g_BloomOriSam, In.vTexUV);

    float4 vBloom = pow(pow(abs(vBloomColor), 2.2f) + pow(abs(vBloomOriTex), 2.2f) , 1.f / 2.2f);

    float4 Out = (vHDRColor);
     
    Out = pow(abs(Out), 2.2f);
    vBloom = pow(abs(vBloom), 2.2f);

    Out += vBloom;

    return pow(abs(Out), 1 / 2.2f);
}

technique DefaultTechnique
{ 
    pass Pass0
    {
		//ZWriteEnable = false;
		Lighting = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
    }
}