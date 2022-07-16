matrix world;
matrix view;
matrix proj;


texture ExtractBrightnessTex;
sampler ExtractBrightnessSam = sampler_state
{
    texture = ExtractBrightnessTex;

    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MIPFILTER = LINEAR;
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

float4 PS_MAIN(float2 vUV : TEXCOORD0) : COLOR0
{
    float4 BrightColor = (float4)0.f;
    float4 FragColor = tex2D(ExtractBrightnessSam, vUV);

    float brightness = dot(FragColor.rgb, float3(0.2126f, 0.7152f, 0.0722f));
    if (brightness > 0.75)
        BrightColor = float4(FragColor.rgb, 1.0);

    return BrightColor;
}

technique DefaultTechnique
{
    pass Pass0
    {
        //ZWriteEnable = false;
        lighting = false;
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
    }
}