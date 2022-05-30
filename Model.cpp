#include "Model.h"

Model::Model() 
{

}

//DESTRUCTOR//
Model::~Model()
{

}

//RETURNS POLYGONS//
const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

//RETUNS VERTICES//
const vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

//RETURNS TRANSFORMED VERTICES//
const vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformed_vertices;
}

//RETURNS VECTOR CONTAINING POLYGONS SIZE//
size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

//RETURNS VECTOR CONTAINING VERTEX SIZE//
size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

//ADDING VERTEX TO VECTOR//
void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
}

//ADDING POLYGON TO VECTOR//
void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

//APPLYING TRANSOFRM TO LOCAL VERTICES, ORGINAL VERTICES WILL NOT BE CHANGED //
void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	if (flag == false)
	{
		for (Vertex v : _vertices)
		{
			_transformed_vertices.push_back(transform * v);
			flag = true;
		}
	}
	else
	{
		for (int i = 0; i < _vertices.size(); i++)
		{

			_transformed_vertices[i] = transform * _vertices[i];

		}
	}
}

//APPLYING TRANSOFRM TO TRANSFORMED VERTICES//
void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int i = 0; i < _transformed_vertices.size(); i++)
	{

		_transformed_vertices[i] = transform * _transformed_vertices[i];

	}
}

//DEGOMOGENIZATE ALL VERTICES//
void Model::DehomogenizeTransformedVertices()
{
	for (int i = 0; i < _transformed_vertices.size(); i++)
	{

		_transformed_vertices[i] = _transformed_vertices[i].Dehomogenize(_transformed_vertices[i]);

	} 
}