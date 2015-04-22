#include "../include/mesh.h"
#include "../lib/rapidjson/document.h"
#include "../include/resourcemanager.h"

using namespace rapidjson;

Ptr<Mesh> Mesh::Create()
{
  return new Mesh();
}
/*MIKEL*/
Ptr<Mesh> Mesh::Create(const String& filename)
{
	String MeshData = String::Read(filename);
	rapidjson::Document document;
	document.Parse<0>(MeshData.ToCString());
	String Dir = filename.ExtractDir();
	String Null = "";
	if (Dir != Null) Dir += String("/");
	//Comprobaciones
	if (document.HasParseError()) return nullptr;
	if (!document.IsObject()) return nullptr;
	if (!document.HasMember("submeshes")) return nullptr;
	if (!document["submeshes"].IsArray()) return nullptr;

	Ptr<Mesh> PtrToMesh = new Mesh(filename);

	//CrearSubMeshes
	for (int i = 0; i < document["submeshes"].Size(); i++)
	{
		const rapidjson::Value &MyMesh = document["submeshes"][i];
		String TextureName = MyMesh["texture"].GetString();
		Ptr<Texture> MyTexture = ResourceManager::Instance()->LoadTexture(Dir + TextureName);
		Ptr<Submesh> MySubmesh = Submesh::Create(MyTexture);
		for (int j = 0; j < MyMesh["indices"].Size(); j += 3)
		{
			uint32 v0 = MyMesh["indices"][j].GetInt();
			uint32 v1 = MyMesh["indices"][j + 1].GetInt();
			uint32 v2 = MyMesh["indices"][j + 2].GetInt();
			MySubmesh->AddTriangle(v0, v1, v2);
		}
		for (int j = 0; j < MyMesh["coords"].Size() / 3; j++)
		{
			glm::vec3 Position;
			Position.x = MyMesh["coords"][3 * j].GetDouble();
			Position.y = MyMesh["coords"][3 * j + 1].GetDouble();
			Position.z = MyMesh["coords"][3 * j + 2].GetDouble();
			glm::vec2 TexCoords;
			TexCoords.s = MyMesh["texcoords"][2 * j].GetDouble();
			TexCoords.t = MyMesh["texcoords"][2 * j + 1].GetDouble();
			Vertex MyVertice(Position, TexCoords);
			MySubmesh->AddVertex(MyVertice);
		}
		PtrToMesh->AddSubmesh(MySubmesh);
	}
	return PtrToMesh;

}
//Ptr<Mesh> Mesh::Create(const String& filename)
//{
//  String read = String::Read(filename);
//  if (read == "") return nullptr;
//
//  Document document;
//  document.Parse<0>(read.ToCString());
//  if (document.HasParseError()) return nullptr;
//  if (!document.IsObject()) return nullptr;
//  if (!document.HasMember("submeshes")) return nullptr;
//  if (!document["submeshes"].IsArray()) return nullptr;
//  SizeType size = document["submeshes"].Size();
//  const Value& submeshes = document["submeshes"];
//
//  Mesh *mesh = new Mesh();
//  for (SizeType i = 0; i < size; i++)
//  {
//    if (submeshes[i].IsObject())
//    {
//      Ptr<Submesh> submesh = Submesh::Create();
//      if (submeshes[i].HasMember("texture")){
//        String strTexture = submeshes[i]["texture"].GetString();
//        String dir = filename.ExtractDir();
//        if (dir != ""){
//          String ruta = "/";
//          strTexture = dir + ruta + strTexture;
//        }
//        Ptr<Texture> tex = Texture::Create(strTexture);
//        submesh->SetTexture(tex);
//      }
//      if (submeshes[i].HasMember("indices"))
//        if (submeshes[i]["indices"].IsArray()){
//          const Value& indices = submeshes[i]["indices"];
//          SizeType numInd = indices.Size();
//          for (SizeType j = 0; j < numInd; j += 3)
//            submesh->AddTriangle(indices[j].GetInt(), indices[j + 1].GetInt(), indices[j + 2].GetInt());
//        }
//      if (submeshes[i].HasMember("coords") && submeshes[i].HasMember("texcoords"))
//        if (submeshes[i]["coords"].IsArray() && submeshes[i]["texcoords"].IsArray()){
//          
//          SizeType numCoords = submeshes[i]["coords"].Size();
//          SizeType numTexCoords = submeshes[i]["texcoords"].Size();
//
//          for (SizeType j = 0, z = 0; j < numCoords; j += 3, z+=2)
//          {
//            vec3 coord;
//            vec2 texcoord;
//            coord.x = submeshes[i]["coords"][j].GetDouble();
//            coord.y = submeshes[i]["coords"][j + 1].GetDouble();
//            coord.z = submeshes[i]["coords"][j + 2].GetDouble();
//
//            if (z < numTexCoords){
//              texcoord.x = submeshes[i]["texcoords"][z].GetDouble();
//              texcoord.y = submeshes[i]["texcoords"][z + 1].GetDouble();
//            }
//            Vertex vertice(coord, texcoord);
//            submesh->AddVertex(vertice);
//          }
//         
//        }
//      mesh->AddSubmesh(submesh);
//    }
//  }
//  mesh->mFilename = filename;
//  return mesh;
//}

void Mesh::Render()
{
  uint32 numSubMeshes = mSubmeshes.Size();
  for (uint32 i = 0; i < numSubMeshes; i++)
    mSubmeshes[i]->Render();
}