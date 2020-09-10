#pragma once
#include <optional>
#include <string>
#include <vector>
#include <variant>
#include <memory>
#include <iostream>

namespace Svg {

	struct Rgb {
		size_t red = 0;
		size_t green = 0;
		size_t blue = 0;
	};

	struct Rgba : Rgb {
		double alpha;
	};

	struct Point {
		double x = 0;
		double y = 0;
	};

	struct Color {
		Color() {}
		Color(std::string color_) : color(color_) {}
		Color(Rgb color_) : color(color_) {}
		Color(Rgba color_) : color(color_) {}
		Color(const char* color_) : color(color_) {}
		Color(size_t red, size_t green, size_t blue) {
			color = Rgb{ red,green,blue };
		}
		Color(size_t red, size_t green, size_t blue, double alpha) {
			color = Rgba{ red,green,blue,alpha };
		}
		void Render(std::ostream& out) const;
		std::variant<std::monostate, std::string, Rgb, Rgba> color;
	};

	const Color NoneColor{};

	class Object {
	public:
		virtual Object& SetFillColor(const Color& color) = 0;
		virtual Object& SetStrokeColor(const Color& color) = 0;
		virtual Object& SetStrokeWidth(double width) = 0;
		virtual Object& SetStrokeLineCap(const std::string& linecap) = 0;
		virtual Object& SetStrokeLineJoin(const std::string& linejoin) = 0;
		virtual void Render(std::ostream& out) const = 0;
		virtual ~Object() = default;
	};

	class Circle : public Object {
	public:
		Circle() {}
		Circle& SetFillColor(const Color& color) override {
			fill_color = color;
			return *this;
		}
		Circle& SetStrokeColor(const Color& color) override {
			stroke_color = color;
			return *this;
		}
		Circle& SetStrokeWidth(double width) override {
			stroke_width = width;
			return *this;
		}
		Circle& SetStrokeLineCap(const std::string& linecap) override {
			stroke_linecap = linecap;
			return *this;
		}
		Circle& SetStrokeLineJoin(const std::string& linejoin) override {
			stroke_linejoin = linejoin;
			return *this;
		}
		Circle& SetCenter(Point point) {
			coordinates = point;
			return *this;
		}
		Circle& SetRadius(double r) {
			radius = r;
			return *this;
		}

		void Render(std::ostream& out) const override;

	private:
		Point coordinates = { 0.0, 0.0 };
		double radius = 1.0;
		Color fill_color = NoneColor;
		Color stroke_color = NoneColor;
		double stroke_width = 1.0;
		std::optional<std::string> stroke_linecap;
		std::optional<std::string> stroke_linejoin;
	};

	class Polyline : public Object {
	public:
		Polyline() {}
		Polyline& SetFillColor(const Color& color) override {
			fill_color = color;
			return *this;
		}
		Polyline& SetStrokeColor(const Color& color) override {
			stroke_color = color;
			return *this;
		}
		Polyline& SetStrokeWidth(double width) override {
			stroke_width = width;
			return *this;
		}
		Polyline& SetStrokeLineCap(const std::string& linecap) override {
			stroke_linecap = linecap;
			return *this;
		}
		Polyline& SetStrokeLineJoin(const std::string& linejoin) override {
			stroke_linejoin = linejoin;
			return *this;
		}
		Polyline& AddPoint(Point point) {
			points.push_back(point);
			return *this;
		}
		void Render(std::ostream& out) const override;

	private:
		std::vector<Point> points;
		Color fill_color = NoneColor;
		Color stroke_color = NoneColor;
		double stroke_width = 1.0;
		std::optional<std::string> stroke_linecap;
		std::optional<std::string> stroke_linejoin;
	};

	class Text : public Object {
	public:
		Text() {}
		Text& SetFillColor(const Color& color) override {
			fill_color = color;
			return *this;
		}
		Text& SetStrokeColor(const Color& color) override {
			stroke_color = color;
			return *this;
		}
		Text& SetStrokeWidth(double width) override {
			stroke_width = width;
			return *this;
		}
		Text& SetStrokeLineCap(const std::string& linecap) override {
			stroke_linecap = linecap;
			return *this;
		}
		Text& SetStrokeLineJoin(const std::string& linejoin) override {
			stroke_linejoin = linejoin;
			return *this;
		}
		Text& SetPoint(Point point) {
			reference_point = point;
			return *this;
		}
		Text& SetOffset(Point point) {
			offset = point;
			return *this;
		}
		Text& SetFontSize(uint32_t size) {
			type_size = size;
			return *this;
		}
		Text& SetFontFamily(const std::string& font) {
			type_name = font;
			return *this;
		}
		Text& SetData(const std::string& txt) {
			text = txt;
			return *this;
		}
		Text& SetFontWeight(const std::string& weight) {
			font_weight = weight;
			return *this;
		}
		void Render(std::ostream& out) const override;
	private:
		Color fill_color = NoneColor;
		Color stroke_color = NoneColor;
		std::optional<std::string> stroke_linecap;
		std::optional<std::string> stroke_linejoin;
		Point reference_point = { 0, 0 };
		Point offset = { 0, 0 };
		uint32_t type_size = 1;
		std::optional<std::string> type_name;
		double stroke_width = 1.0;
		std::string text;
		std::optional<std::string> font_weight;
	};

	class Document {
	public:
		Document() {};
		template <typename Type>
		void Add(Type object) {
			objects.push_back(std::make_shared<Type>(std::move(object)));
		}
		void Render(std::ostream& out) const;
	private:
		std::vector<std::shared_ptr<Object>> objects;
	};
}
