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
 138;
 -202.58981;416.34952;20.42818;,
 202.58981;416.34952;20.42818;,
 202.58981;416.34952;-20.42818;,
 -202.58981;416.34952;-20.42818;,
 -220.51618;388.92545;-25.53521;,
 220.51618;388.92545;-25.53521;,
 220.51618;169.53273;-25.53521;,
 -220.51618;169.53273;-25.53521;,
 -202.58981;142.10866;-20.42818;,
 202.58981;142.10866;-20.42818;,
 202.58981;142.10866;20.42818;,
 -202.58981;142.10866;20.42818;,
 -220.51618;169.53273;25.53521;,
 220.51618;169.53273;25.53521;,
 220.51618;388.92545;25.53521;,
 -220.51618;388.92545;25.53521;,
 253.23734;388.92535;20.42818;,
 253.23734;169.53278;20.42818;,
 253.23734;169.53278;-20.42818;,
 253.23734;388.92535;-20.42818;,
 -253.23734;169.53278;20.42818;,
 -253.23734;388.92535;20.42818;,
 -253.23734;388.92535;-20.42818;,
 -253.23734;169.53278;-20.42818;,
 -202.58981;416.34952;-20.42818;,
 202.58981;416.34952;-20.42818;,
 220.51618;388.92545;-25.53521;,
 -220.51618;169.53273;-25.53521;,
 220.51618;169.53273;-25.53521;,
 202.58981;142.10866;-20.42818;,
 -220.51618;388.92545;25.53521;,
 220.51618;388.92545;25.53521;,
 202.58981;416.34952;20.42818;,
 -202.58981;142.10866;20.42818;,
 202.58981;142.10866;20.42818;,
 220.51618;169.53273;25.53521;,
 253.23734;388.92535;-20.42818;,
 253.23734;169.53278;-20.42818;,
 253.23734;169.53278;20.42818;,
 -253.23734;388.92535;-20.42818;,
 -253.23734;388.92535;20.42818;,
 -253.23734;169.53278;-20.42818;,
 -82.85710;143.88903;-12.45164;,
 82.85710;143.88903;-12.45164;,
 82.85710;121.79521;-12.45164;,
 -82.85710;121.79521;-12.45164;,
 82.85710;143.88903;-12.45164;,
 82.85710;143.88903;12.45164;,
 82.85710;121.79521;12.45164;,
 82.85710;121.79521;-12.45164;,
 82.85710;143.88903;12.45164;,
 -82.85710;143.88903;12.45164;,
 -82.85710;121.79521;12.45164;,
 82.85710;121.79521;12.45164;,
 -82.85710;143.88903;12.45164;,
 -82.85710;143.88903;-12.45164;,
 -82.85710;121.79521;-12.45164;,
 -82.85710;121.79521;12.45164;,
 82.85710;143.88903;-12.45164;,
 -82.85710;143.88903;-12.45164;,
 -82.85710;121.79521;-12.45164;,
 82.85710;121.79521;-12.45164;,
 -76.50202;121.79279;-9.41730;,
 76.50202;121.79279;-9.41730;,
 64.89224;88.19791;-9.41730;,
 -64.89224;88.19791;-9.41730;,
 76.50202;54.60303;-9.41730;,
 -76.50202;54.60303;-9.41730;,
 76.50202;121.79279;-9.41730;,
 76.50202;121.79279;9.41730;,
 64.89224;88.19791;9.41730;,
 64.89224;88.19791;-9.41730;,
 76.50202;54.60303;9.41730;,
 76.50202;54.60303;-9.41730;,
 76.50202;121.79279;9.41730;,
 -76.50202;121.79279;9.41730;,
 -64.89224;88.19791;9.41730;,
 64.89224;88.19791;9.41730;,
 -76.50202;54.60303;9.41730;,
 76.50202;54.60303;9.41730;,
 -76.50202;121.79279;9.41730;,
 -76.50202;121.79279;-9.41730;,
 -64.89224;88.19791;-9.41730;,
 -64.89224;88.19791;9.41730;,
 -76.50202;54.60303;-9.41730;,
 -76.50202;54.60303;9.41730;,
 76.50202;121.79279;-9.41730;,
 -76.50202;121.79279;-9.41730;,
 -76.50202;54.60303;-9.41730;,
 76.50202;54.60303;-9.41730;,
 -83.27145;60.05214;-18.55715;,
 83.27145;60.05214;-18.55715;,
 150.00000;0.44245;-18.55715;,
 -150.00000;0.44245;-18.55715;,
 83.27145;60.05214;-18.55715;,
 83.27145;60.05214;18.55715;,
 150.00000;0.44245;18.55715;,
 150.00000;0.44245;-18.55715;,
 83.27145;60.05214;18.55715;,
 -83.27145;60.05214;18.55715;,
 -150.00000;0.44245;18.55715;,
 150.00000;0.44245;18.55715;,
 -83.27145;60.05214;18.55715;,
 -83.27145;60.05214;-18.55715;,
 -150.00000;0.44245;-18.55715;,
 -150.00000;0.44245;18.55715;,
 83.27145;60.05214;-18.55715;,
 -83.27145;60.05214;-18.55715;,
 -150.00000;0.44245;-18.55715;,
 150.00000;0.44245;-18.55715;,
 -106.85601;104.43723;-107.57188;,
 106.85601;104.43723;-107.57188;,
 106.85601;70.50079;-182.37067;,
 -106.85601;70.50079;-182.37067;,
 106.85601;0.22808;-182.37067;,
 -106.85601;0.22808;-182.37067;,
 106.85601;104.43723;-107.57188;,
 106.85601;104.43723;-20.78927;,
 106.85601;70.50079;-20.78927;,
 106.85601;70.50079;-182.37067;,
 106.85601;0.22808;-20.78927;,
 106.85601;0.22808;-182.37067;,
 106.85601;104.43723;-20.78927;,
 -106.85601;104.43723;-20.78927;,
 -106.85601;70.50079;-20.78927;,
 106.85601;70.50079;-20.78927;,
 -106.85601;0.22808;-20.78927;,
 106.85601;0.22808;-20.78927;,
 -106.85601;104.43723;-20.78927;,
 -106.85601;104.43723;-107.57188;,
 -106.85601;70.50079;-182.37067;,
 -106.85601;70.50079;-20.78927;,
 -106.85601;0.22808;-182.37067;,
 -106.85601;0.22808;-20.78927;,
 106.85601;104.43723;-107.57188;,
 -106.85601;104.43723;-107.57188;,
 -106.85601;0.22808;-182.37067;,
 106.85601;0.22808;-182.37067;;
 
 58;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,4;,
 4;27,28,29,8;,
 4;30,31,32,0;,
 4;33,34,35,12;,
 4;25,32,16,36;,
 4;34,29,37,38;,
 4;0,24,39,40;,
 4;8,33,20,41;,
 4;28,26,36,37;,
 4;31,35,38,16;,
 4;4,27,41,39;,
 4;12,30,40,20;,
 3;25,36,26;,
 3;4,39,24;,
 3;28,37,29;,
 3;31,16,32;,
 3;8,41,27;,
 3;34,38,35;,
 3;0,40,30;,
 3;12,20,33;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;54,47,58,59;,
 4;60,61,48,57;,
 4;62,63,64,65;,
 4;65,64,66,67;,
 4;68,69,70,71;,
 4;71,70,72,73;,
 4;74,75,76,77;,
 4;77,76,78,79;,
 4;80,81,82,83;,
 4;83,82,84,85;,
 4;80,69,86,87;,
 4;88,89,72,85;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;102,95,106,107;,
 4;108,109,96,105;,
 4;110,111,112,113;,
 4;113,112,114,115;,
 4;116,117,118,119;,
 4;119,118,120,121;,
 4;122,123,124,125;,
 4;125,124,126,127;,
 4;128,129,130,131;,
 4;131,130,132,133;,
 4;128,117,134,135;,
 4;136,137,120,133;;
 
 MeshMaterialList {
  4;
  58;
  0,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.144314;0.291765;0.332549;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.291765;0.316863;0.301176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.633726;0.633726;0.633726;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\model\\TvScreen.jpg";
   }
  }
 }
 MeshNormals {
  65;
  -0.245597;0.969372;0.000000;,
  0.245597;0.969372;0.000000;,
  -0.076405;0.115415;-0.990375;,
  0.076405;0.115415;-0.990375;,
  -0.076405;-0.115415;-0.990375;,
  0.076405;-0.115415;-0.990375;,
  -0.245597;-0.969372;0.000000;,
  0.245597;-0.969372;-0.000000;,
  -0.076405;-0.115415;0.990375;,
  0.076405;-0.115415;0.990375;,
  -0.076405;0.115415;0.990375;,
  0.076405;0.115415;0.990375;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.074449;0.229393;-0.970483;,
  0.074449;0.229393;-0.970483;,
  0.074449;-0.229393;-0.970483;,
  -0.074449;-0.229393;-0.970483;,
  0.074449;0.229393;0.970483;,
  -0.074449;0.229393;0.970483;,
  -0.074449;-0.229393;0.970483;,
  0.074449;-0.229393;0.970483;,
  0.476150;0.879364;0.000000;,
  0.476149;-0.879364;-0.000000;,
  -0.476150;0.879364;0.000000;,
  -0.476149;-0.879364;0.000000;,
  0.152729;0.138283;-0.978546;,
  0.152729;-0.138283;-0.978546;,
  0.152729;-0.138283;0.978546;,
  0.152729;0.138283;0.978546;,
  -0.152729;-0.138283;-0.978546;,
  -0.152729;0.138283;-0.978546;,
  -0.152729;0.138283;0.978546;,
  -0.152729;-0.138283;0.978546;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.945153;-0.326628;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.945153;0.326628;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.945153;-0.326628;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.945153;0.326628;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.356534;0.934282;0.000000;,
  0.666206;0.745768;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.356534;0.934282;0.000000;,
  -0.666206;0.745768;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.977409;-0.211358;,
  0.000000;0.910655;-0.413167;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  58;
  4;0,1,1,0;,
  4;2,3,5,4;,
  4;6,7,7,6;,
  4;8,9,11,10;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,15,3,2;,
  4;4,5,16,17;,
  4;10,11,18,19;,
  4;20,21,9,8;,
  4;1,1,22,22;,
  4;7,7,23,23;,
  4;0,0,24,24;,
  4;6,6,25,25;,
  4;5,3,26,27;,
  4;11,9,28,29;,
  4;2,4,30,31;,
  4;8,10,32,33;,
  3;15,26,3;,
  3;2,31,14;,
  3;5,27,16;,
  3;11,29,18;,
  3;17,30,4;,
  3;21,28,9;,
  3;19,32,10;,
  3;8,33,20;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;41,41,42,42;,
  4;42,42,43,43;,
  4;44,44,44,44;,
  4;44,44,44,44;,
  4;45,45,46,46;,
  4;46,46,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,52,52;,
  4;53,53,53,53;,
  4;54,54,55,55;,
  4;54,51,51,54;,
  4;56,56,56,56;,
  4;57,57,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;62,62,62,62;,
  4;63,63,57,57;,
  4;64,64,64,64;;
 }
 MeshTextureCoords {
  138;
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
