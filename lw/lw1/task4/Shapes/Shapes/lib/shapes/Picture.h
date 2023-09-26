#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "./shape/Shape.h"
#include "../canvas/ICanvas.h"

class Picture
{
public:
	using ShapeElement = std::unique_ptr<Shape>;
	using ShapeList = std::unordered_map<std::string, ShapeElement>;

	const std::unordered_map<std::string, ShapeType> ShapeNameToType = {
		{"circle", ShapeType::Circle},
		{"triangle", ShapeType::Triangle},
		{"rectangle", ShapeType::Rectangle},
		{"text", ShapeType::Text},
		{"line", ShapeType::Line},
	};

	Picture(std::shared_ptr<ICanvas>&& canvas)
		: m_canvas(std::move(canvas))
	{
	}

	void AddShape(const std::string& id, ShapeElement&& shape)
	{
		if (m_shapes.contains(id))
		{
			throw std::runtime_error("Shape with id " + id + " already exists");
		}
		m_shapes.insert({id, std::move(shape)});
		m_insertOrderedIds.push_back(id);
	}

	void DeleteShape(const std::string& id)
	{
		EnsureElementExists(id);
		m_shapes.erase(id);
		std::erase(m_insertOrderedIds, id);
	}

	void DrawPicture() const
	{
		for (const auto& [id, shape] : m_shapes)
		{
			shape->Draw(*m_canvas.get());
		}
	}

	const std::vector<std::string>& GetIds()
	{
		return m_insertOrderedIds;
	}

	void DrawShape(const std::string& id) const
	{
		EnsureElementExists(id);
		m_shapes.at(id)->Draw(*m_canvas.get());
	}

	const ShapeElement& GetShape(const std::string& id) const
	{
		EnsureElementExists(id);
		return m_shapes.at(id);
	}

	ShapeElement& GetShape(const std::string& id)
	{
		EnsureElementExists(id);
		return m_shapes.at(id);
	}

private:
	void EnsureElementExists(const std::string& id) const
	{
		if (!m_shapes.contains(id))
		{
			throw std::runtime_error("Shape does not exists " + id);
		}
	}

	std::vector<std::string> m_insertOrderedIds;
	ShapeList m_shapes = {};
	std::shared_ptr<ICanvas> m_canvas;
};
