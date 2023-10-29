xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 286;
 21.98388;174.88138;-17.13772;,
 21.98388;1.07210;-17.13772;,
 -20.72403;1.07210;-17.13772;,
 -20.72403;174.88138;-17.13772;,
 21.98388;1.07210;-17.13772;,
 21.98388;1.07210;17.25885;,
 -20.72403;1.07210;17.25885;,
 -20.72403;1.07210;-17.13772;,
 21.98388;1.07210;17.25885;,
 21.98388;174.88138;17.25885;,
 -20.72403;174.88138;17.25885;,
 -20.72403;1.07210;17.25885;,
 21.98388;174.88138;17.25885;,
 21.98388;174.88138;-17.13772;,
 -20.72403;174.88138;-17.13772;,
 -20.72403;174.88138;17.25885;,
 21.98388;1.07210;-17.13772;,
 21.98388;174.88138;-17.13772;,
 -20.72403;174.88138;-17.13772;,
 -20.72403;1.07210;-17.13772;,
 22.06323;160.35861;-6.43675;,
 34.93671;160.35861;0.00000;,
 22.06323;155.80713;-4.55147;,
 34.93671;160.35861;0.00000;,
 22.06323;153.92184;0.00000;,
 34.93671;160.35861;0.00000;,
 22.06323;155.80713;4.55147;,
 34.93671;160.35861;0.00000;,
 22.06323;160.35861;6.43675;,
 22.06323;160.35861;0.00000;,
 22.06323;160.35861;-6.43675;,
 22.06323;155.80713;-4.55147;,
 22.06323;153.92184;0.00000;,
 22.06323;155.80713;4.55147;,
 22.06323;160.35861;6.43675;,
 22.06323;160.35861;-6.43675;,
 34.93671;160.35861;0.00000;,
 22.06323;155.80713;-4.55147;,
 34.93671;160.35861;0.00000;,
 22.06323;153.92184;0.00000;,
 34.93671;160.35861;0.00000;,
 22.06323;155.80713;4.55147;,
 34.93671;160.35861;0.00000;,
 22.06323;160.35861;6.43675;,
 22.06323;160.35861;0.00000;,
 22.06323;160.35861;-6.43675;,
 22.06323;155.80713;-4.55147;,
 22.06323;153.92184;0.00000;,
 22.06323;155.80713;4.55147;,
 22.06323;160.35861;6.43675;,
 22.06323;160.35861;6.43675;,
 22.06323;160.35861;0.00000;,
 22.06323;160.35861;-6.43675;,
 34.93671;160.35861;0.00000;,
 22.06323;160.35861;-6.43675;,
 34.93671;160.35861;0.00000;,
 22.06323;160.35861;0.00000;,
 22.06323;160.35861;6.43675;,
 22.06323;160.35861;0.00000;,
 22.06323;160.35861;6.43675;,
 34.93671;160.35861;0.00000;,
 22.06323;160.35861;-6.43675;,
 22.15581;147.33859;-6.43675;,
 35.02929;147.33859;0.00000;,
 22.15581;142.78714;-4.55147;,
 35.02929;147.33859;0.00000;,
 22.15581;140.90186;0.00000;,
 35.02929;147.33859;0.00000;,
 22.15581;142.78714;4.55147;,
 35.02929;147.33859;0.00000;,
 22.15581;147.33859;6.43675;,
 35.02929;147.33859;0.00000;,
 22.15581;151.89008;4.55146;,
 35.02929;147.33859;0.00000;,
 22.15581;153.92184;0.00000;,
 35.02929;147.33859;0.00000;,
 22.15581;151.89008;-4.55146;,
 35.02929;147.33859;0.00000;,
 22.15581;147.33859;-6.43675;,
 22.15581;147.33859;0.00000;,
 22.15581;147.33859;-6.43675;,
 22.15581;142.78714;-4.55147;,
 22.15581;140.90186;0.00000;,
 22.15581;142.78714;4.55147;,
 22.15581;147.33859;6.43675;,
 22.15581;151.89008;4.55146;,
 22.15581;153.92184;0.00000;,
 22.15581;151.89008;-4.55146;,
 22.15581;134.44357;-6.43675;,
 35.02929;134.44357;0.00000;,
 22.15581;129.89212;-4.55147;,
 35.02929;134.44357;0.00000;,
 22.15581;128.00684;0.00000;,
 35.02929;134.44357;0.00000;,
 22.15581;129.89212;4.55147;,
 35.02929;134.44357;0.00000;,
 22.15581;134.44357;6.43675;,
 35.02929;134.44357;0.00000;,
 22.15581;138.99506;4.55146;,
 35.02929;134.44357;0.00000;,
 22.15581;140.90186;0.00000;,
 35.02929;134.44357;0.00000;,
 22.15581;138.99506;-4.55146;,
 35.02929;134.44357;0.00000;,
 22.15581;134.44357;-6.43675;,
 22.15581;134.44357;0.00000;,
 22.15581;134.44357;-6.43675;,
 22.15581;129.89212;-4.55147;,
 22.15581;128.00684;0.00000;,
 22.15581;129.89212;4.55147;,
 22.15581;134.44357;6.43675;,
 22.15581;138.99506;4.55146;,
 22.15581;140.90186;0.00000;,
 22.15581;138.99506;-4.55146;,
 22.15581;121.42357;-6.43675;,
 35.02929;121.42357;0.00000;,
 22.15581;116.87210;-4.55147;,
 35.02929;121.42357;0.00000;,
 22.15581;114.98682;0.00000;,
 35.02929;121.42357;0.00000;,
 22.15581;116.87210;4.55147;,
 35.02929;121.42357;0.00000;,
 22.15581;121.42357;6.43675;,
 35.02929;121.42357;0.00000;,
 22.15581;125.97504;4.55146;,
 35.02929;121.42357;0.00000;,
 22.15581;128.00684;0.00000;,
 35.02929;121.42357;0.00000;,
 22.15581;125.97504;-4.55146;,
 35.02929;121.42357;0.00000;,
 22.15581;121.42357;-6.43675;,
 22.15581;121.42357;0.00000;,
 22.15581;121.42357;-6.43675;,
 22.15581;116.87210;-4.55147;,
 22.15581;114.98682;0.00000;,
 22.15581;116.87210;4.55147;,
 22.15581;121.42357;6.43675;,
 22.15581;125.97504;4.55146;,
 22.15581;128.00684;0.00000;,
 22.15581;125.97504;-4.55146;,
 22.15581;108.33000;-6.43675;,
 35.02929;108.33000;0.00000;,
 22.15581;103.77853;-4.55147;,
 35.02929;108.33000;0.00000;,
 22.15581;101.89325;0.00000;,
 35.02929;108.33000;0.00000;,
 22.15581;103.77853;4.55147;,
 35.02929;108.33000;0.00000;,
 22.15581;108.33000;6.43675;,
 35.02929;108.33000;0.00000;,
 22.15581;112.88147;4.55146;,
 35.02929;108.33000;0.00000;,
 22.15581;114.98682;0.00000;,
 35.02929;108.33000;0.00000;,
 22.15581;112.88147;-4.55146;,
 35.02929;108.33000;0.00000;,
 22.15581;108.33000;-6.43675;,
 22.15581;108.33000;0.00000;,
 22.15581;108.33000;-6.43675;,
 22.15581;103.77853;-4.55147;,
 22.15581;101.89325;0.00000;,
 22.15581;103.77853;4.55147;,
 22.15581;108.33000;6.43675;,
 22.15581;112.88147;4.55146;,
 22.15581;114.98682;0.00000;,
 22.15581;112.88147;-4.55146;,
 22.15581;95.31000;-6.43675;,
 35.02929;95.31000;0.00000;,
 22.15581;90.75853;-4.55147;,
 35.02929;95.31000;0.00000;,
 22.15581;88.87325;0.00000;,
 35.02929;95.31000;0.00000;,
 22.15581;90.75853;4.55147;,
 35.02929;95.31000;0.00000;,
 22.15581;95.31000;6.43675;,
 35.02929;95.31000;0.00000;,
 22.15581;99.86147;4.55146;,
 35.02929;95.31000;0.00000;,
 22.15581;101.89325;0.00000;,
 35.02929;95.31000;0.00000;,
 22.15581;99.86147;-4.55146;,
 35.02929;95.31000;0.00000;,
 22.15581;95.31000;-6.43675;,
 22.15581;95.31000;0.00000;,
 22.15581;95.31000;-6.43675;,
 22.15581;90.75853;-4.55147;,
 22.15581;88.87325;0.00000;,
 22.15581;90.75853;4.55147;,
 22.15581;95.31000;6.43675;,
 22.15581;99.86147;4.55146;,
 22.15581;101.89325;0.00000;,
 22.15581;99.86147;-4.55146;,
 22.15581;82.41498;-6.43675;,
 35.02929;82.41498;0.00000;,
 22.15581;77.86351;-4.55147;,
 35.02929;82.41498;0.00000;,
 22.15581;75.97823;0.00000;,
 35.02929;82.41498;0.00000;,
 22.15581;77.86351;4.55147;,
 35.02929;82.41498;0.00000;,
 22.15581;82.41498;6.43675;,
 35.02929;82.41498;0.00000;,
 22.15581;86.96645;4.55146;,
 35.02929;82.41498;0.00000;,
 22.15581;88.87325;0.00000;,
 35.02929;82.41498;0.00000;,
 22.15581;86.96645;-4.55146;,
 35.02929;82.41498;0.00000;,
 22.15581;82.41498;-6.43675;,
 22.15581;82.41498;0.00000;,
 22.15581;82.41498;-6.43675;,
 22.15581;77.86351;-4.55147;,
 22.15581;75.97823;0.00000;,
 22.15581;77.86351;4.55147;,
 22.15581;82.41498;6.43675;,
 22.15581;86.96645;4.55146;,
 22.15581;88.87325;0.00000;,
 22.15581;86.96645;-4.55146;,
 22.15581;69.39497;-6.43675;,
 35.02929;69.39497;0.00000;,
 22.15581;64.84351;-4.55147;,
 35.02929;69.39497;0.00000;,
 22.15581;62.95822;0.00000;,
 35.02929;69.39497;0.00000;,
 22.15581;64.84351;4.55147;,
 35.02929;69.39497;0.00000;,
 22.15581;69.39497;6.43675;,
 35.02929;69.39497;0.00000;,
 22.15581;73.94644;4.55146;,
 35.02929;69.39497;0.00000;,
 22.15581;75.97823;0.00000;,
 35.02929;69.39497;0.00000;,
 22.15581;73.94644;-4.55146;,
 35.02929;69.39497;0.00000;,
 22.15581;69.39497;-6.43675;,
 22.15581;69.39497;0.00000;,
 22.15581;69.39497;-6.43675;,
 22.15581;64.84351;-4.55147;,
 22.15581;62.95822;0.00000;,
 22.15581;64.84351;4.55147;,
 22.15581;69.39497;6.43675;,
 22.15581;73.94644;4.55146;,
 22.15581;75.97823;0.00000;,
 22.15581;73.94644;-4.55146;,
 22.06323;56.27423;6.43675;,
 34.93671;56.27423;-0.00000;,
 22.06323;60.82570;4.55147;,
 34.93671;56.27423;-0.00000;,
 22.06323;62.71098;0.00000;,
 34.93671;56.27423;-0.00000;,
 22.06323;60.82570;-4.55147;,
 34.93671;56.27423;-0.00000;,
 22.06323;56.27423;-6.43675;,
 22.06323;56.27423;-0.00000;,
 22.06323;56.27423;6.43675;,
 22.06323;60.82570;4.55147;,
 22.06323;62.71098;0.00000;,
 22.06323;60.82570;-4.55147;,
 22.06323;56.27423;-6.43675;,
 22.06323;56.27423;6.43675;,
 34.93671;56.27423;-0.00000;,
 22.06323;60.82570;4.55147;,
 34.93671;56.27423;-0.00000;,
 22.06323;62.71098;0.00000;,
 34.93671;56.27423;-0.00000;,
 22.06323;60.82570;-4.55147;,
 34.93671;56.27423;-0.00000;,
 22.06323;56.27423;-6.43675;,
 22.06323;56.27423;-0.00000;,
 22.06323;56.27423;6.43675;,
 22.06323;60.82570;4.55147;,
 22.06323;62.71098;0.00000;,
 22.06323;60.82570;-4.55147;,
 22.06323;56.27423;-6.43675;,
 22.06323;56.27423;-6.43675;,
 22.06323;56.27423;-0.00000;,
 22.06323;56.27423;6.43675;,
 34.93671;56.27423;-0.00000;,
 22.06323;56.27423;6.43675;,
 34.93671;56.27423;-0.00000;,
 22.06323;56.27423;-0.00000;,
 22.06323;56.27423;-6.43675;,
 22.06323;56.27423;-0.00000;,
 22.06323;56.27423;-6.43675;,
 34.93671;56.27423;-0.00000;,
 22.06323;56.27423;6.43675;;
 
 156;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 3;20,21,22;,
 3;22,23,24;,
 3;24,25,26;,
 3;26,27,28;,
 3;29,30,31;,
 3;29,31,32;,
 3;29,32,33;,
 3;29,33,34;,
 3;35,36,37;,
 3;37,38,39;,
 3;39,40,41;,
 3;41,42,43;,
 3;44,45,46;,
 3;44,46,47;,
 3;44,47,48;,
 3;44,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;68,69,70;,
 3;70,71,72;,
 3;72,73,74;,
 3;74,75,76;,
 3;76,77,78;,
 3;79,80,81;,
 3;79,81,82;,
 3;79,82,83;,
 3;79,83,84;,
 3;79,84,85;,
 3;79,85,86;,
 3;79,86,87;,
 3;79,87,80;,
 3;88,89,90;,
 3;90,91,92;,
 3;92,93,94;,
 3;94,95,96;,
 3;96,97,98;,
 3;98,99,100;,
 3;100,101,102;,
 3;102,103,104;,
 3;105,106,107;,
 3;105,107,108;,
 3;105,108,109;,
 3;105,109,110;,
 3;105,110,111;,
 3;105,111,112;,
 3;105,112,113;,
 3;105,113,106;,
 3;114,115,116;,
 3;116,117,118;,
 3;118,119,120;,
 3;120,121,122;,
 3;122,123,124;,
 3;124,125,126;,
 3;126,127,128;,
 3;128,129,130;,
 3;131,132,133;,
 3;131,133,134;,
 3;131,134,135;,
 3;131,135,136;,
 3;131,136,137;,
 3;131,137,138;,
 3;131,138,139;,
 3;131,139,132;,
 3;140,141,142;,
 3;142,143,144;,
 3;144,145,146;,
 3;146,147,148;,
 3;148,149,150;,
 3;150,151,152;,
 3;152,153,154;,
 3;154,155,156;,
 3;157,158,159;,
 3;157,159,160;,
 3;157,160,161;,
 3;157,161,162;,
 3;157,162,163;,
 3;157,163,164;,
 3;157,164,165;,
 3;157,165,158;,
 3;166,167,168;,
 3;168,169,170;,
 3;170,171,172;,
 3;172,173,174;,
 3;174,175,176;,
 3;176,177,178;,
 3;178,179,180;,
 3;180,181,182;,
 3;183,184,185;,
 3;183,185,186;,
 3;183,186,187;,
 3;183,187,188;,
 3;183,188,189;,
 3;183,189,190;,
 3;183,190,191;,
 3;183,191,184;,
 3;192,193,194;,
 3;194,195,196;,
 3;196,197,198;,
 3;198,199,200;,
 3;200,201,202;,
 3;202,203,204;,
 3;204,205,206;,
 3;206,207,208;,
 3;209,210,211;,
 3;209,211,212;,
 3;209,212,213;,
 3;209,213,214;,
 3;209,214,215;,
 3;209,215,216;,
 3;209,216,217;,
 3;209,217,210;,
 3;218,219,220;,
 3;220,221,222;,
 3;222,223,224;,
 3;224,225,226;,
 3;226,227,228;,
 3;228,229,230;,
 3;230,231,232;,
 3;232,233,234;,
 3;235,236,237;,
 3;235,237,238;,
 3;235,238,239;,
 3;235,239,240;,
 3;235,240,241;,
 3;235,241,242;,
 3;235,242,243;,
 3;235,243,236;,
 3;244,245,246;,
 3;246,247,248;,
 3;248,249,250;,
 3;250,251,252;,
 3;253,254,255;,
 3;253,255,256;,
 3;253,256,257;,
 3;253,257,258;,
 3;259,260,261;,
 3;261,262,263;,
 3;263,264,265;,
 3;265,266,267;,
 3;268,269,270;,
 3;268,270,271;,
 3;268,271,272;,
 3;268,272,273;,
 4;274,275,276,277;,
 4;278,279,280,281;,
 4;282,283,284,285;;
 
 MeshMaterialList {
  4;
  156;
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  2,
  2;;
  Material {
   0.523922;0.523922;0.523922;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.097255;0.285490;0.338824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.759216;0.759216;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.009412;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  47;
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.419359;-0.347407;-0.838717;,
  0.447214;-0.632455;-0.632456;,
  0.447215;-0.894426;0.000000;,
  0.447214;-0.632455;0.632456;,
  0.419359;-0.347407;0.838717;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.447214;-0.000001;-0.894427;,
  0.447213;-0.632456;-0.632455;,
  0.447214;-0.894427;0.000000;,
  0.447213;-0.632456;0.632455;,
  0.447214;-0.000001;0.894427;,
  0.447180;0.623576;0.641235;,
  0.455302;0.890337;0.000000;,
  0.447180;0.623576;-0.641235;,
  0.447214;0.631142;0.633767;,
  0.448410;0.893828;0.000000;,
  0.447214;0.631142;-0.633767;,
  0.447214;0.000000;-0.894427;,
  0.447214;-0.632455;-0.632456;,
  0.447214;-0.894427;0.000000;,
  0.447214;-0.632455;0.632456;,
  0.447214;0.000000;0.894427;,
  0.447179;0.623575;0.641237;,
  0.455302;0.890337;0.000000;,
  0.447179;0.623575;-0.641237;,
  0.447136;0.619173;0.645518;,
  0.459321;0.888271;0.000000;,
  0.447136;0.619173;-0.645518;,
  0.447179;0.623576;0.641236;,
  0.455302;0.890337;0.000000;,
  0.447179;0.623576;-0.641236;,
  0.447213;0.631142;0.633766;,
  0.448409;0.893829;0.000000;,
  0.447213;0.631142;-0.633766;,
  0.419359;0.347408;0.838717;,
  0.447214;0.632455;0.632456;,
  0.447214;0.894427;0.000000;,
  0.447214;0.632455;-0.632456;,
  0.419359;0.347408;-0.838717;;
  156;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  3;6,7,7;,
  3;7,7,8;,
  3;8,9,9;,
  3;9,9,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;6,7,7;,
  3;7,7,8;,
  3;8,9,9;,
  3;9,9,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  3;14,15,15;,
  3;15,15,16;,
  3;16,17,17;,
  3;17,17,18;,
  3;18,19,19;,
  3;19,19,20;,
  3;20,21,21;,
  3;21,21,14;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;14,15,15;,
  3;15,15,16;,
  3;16,17,17;,
  3;17,17,18;,
  3;18,22,22;,
  3;22,22,23;,
  3;23,24,24;,
  3;24,24,14;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,30,30;,
  3;30,30,31;,
  3;31,32,32;,
  3;32,32,25;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,33,33;,
  3;33,33,34;,
  3;34,35,35;,
  3;35,35,25;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,36,36;,
  3;36,36,37;,
  3;37,38,38;,
  3;38,38,25;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,39,39;,
  3;39,39,40;,
  3;40,41,41;,
  3;41,41,25;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,36,36;,
  3;36,36,37;,
  3;37,38,38;,
  3;38,38,25;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;42,43,43;,
  3;43,43,44;,
  3;44,45,45;,
  3;45,45,46;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;42,43,43;,
  3;43,43,44;,
  3;44,45,45;,
  3;45,45,46;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;12,12,12,12;;
 }
 MeshTextureCoords {
  286;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}