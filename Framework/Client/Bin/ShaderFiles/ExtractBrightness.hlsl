texture g_FinalTex;
sampler g_FinalSam = sampler_state
{
    texture = g_FinalTex;
};

texture g_BlurTex;
sampler g_BlurSam = sampler_state
{
    texture = g_BlurTex;
};

float4 PS_MAIN(float2 vUV : TEXCOORD0) : COLOR
{
    float BrightColor = 0.f;
    float4 FragColor = tex2D(g_FinalSam, vUV);

    float brightness = dot(FragColor.rgb, float3(0.2126f, 0.7152f, 0.0722f));
    if (brightness > 0.99)
        BrightColor = float4(FragColor.rgb, 1.0);

    return BrightColor;
}

technique DefaultTech
{
    pass Pass0
    {
        ZWriteEnable = false;
        lighting = false;
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_MAIN();
    }
}