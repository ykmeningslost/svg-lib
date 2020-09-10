#include "svg.h"

using namespace std;

namespace Svg {
	void Color::Render(ostream& out) const {
		if (holds_alternative<Rgb>(color)) {
			out << "rgb(" << (get<Rgb>(color)).red << "," << (get<Rgb>(color)).green
				<< "," << (get<Rgb>(color)).blue << ")" << "\\" << '"' << ' ';
		}
		else if (holds_alternative<Rgba>(color)) {
			out << "rgba(" << (get<Rgba>(color)).red << "," << (get<Rgba>(color)).green
				<< "," << (get<Rgba>(color)).blue << ',' <<
				(get<Rgba>(color)).alpha << ")" << "\\" << '"' << ' ';
		}
		else if (holds_alternative<string>(color)) {
			out << get<string>(color) << "\\" << '"' << ' ';
		}
		else {
			out << "none" << "\\" << '"' << ' ';
		}
	}

	void Circle::Render(ostream& out) const {
		out << "<circle " <<
			"cx=\\" << '"' << coordinates.x << "\\" << '"' << ' ' <<
			"cy=\\" << '"' << coordinates.y << "\\" << '"' << ' ' <<
			"r=\\" << '"' << radius << "\\" << '"' << ' ' <<
			"fill=\\" << '"' << ' ';
		fill_color.Render(out);
		out << "stroke=\\" << '"' << ' ';
		stroke_color.Render(out);
		out << "stroke-width=\\" << '"' << stroke_width << "\\" << '"' << ' ';
		out << "/>";
	}

	void Polyline::Render(ostream& out) const {
		out << "<polyline ";
		if (points.size() != 0) {
			out << "points=\\" << '"';
			for (auto& point : points) {
				out << point.x << ',' << point.y << ' ';
			}
			out << "\\" << '"' << ' ';
		}
		out << "fill=\\" << '"';
		fill_color.Render(out);
		out << "stroke=\\" << '"';
		stroke_color.Render(out);
		out << "stroke-width=\\" << '"' << stroke_width << "\\" << '"' << ' ';
		if (stroke_linecap.has_value()) {
			out << "stroke-linecap=\\" << '"' << stroke_linecap.value() << "\\" << '"' << ' ';
		}
		if (stroke_linejoin.has_value()) {
			out << "stroke-linejoin=\\" << '"' << stroke_linejoin.value() << "\\" << '"' << ' ';
		}
		out << "/>";
	}
	void Text::Render(ostream& out) const {
		out << "<text ";
		out << "x=\\" << '"' << reference_point.x << "\\" << '"' << ' ' << "y=\\" << '"' << reference_point.y << "\\" << '"' << ' '
			<< "dx=\\" << '"' << offset.x << "\\" << '"' << ' ' << "dy=\\" << '"' << offset.y << "\\" << '"' << ' '
			<< "font-size=\\" << '"' << type_size << "\\" << '"' << ' ';
		if (type_name.has_value()) {
			out << "font-family=\\" << '"' << type_name.value() << "\\" << '"' << ' ';
		}
		if (font_weight.has_value()) {
			out << "font-weight=\\" << '"' << font_weight.value() << "\\" << '"' << ' ';
		}
		out << "fill=\\" << '"';
		fill_color.Render(out);
		out << "stroke=\\" << '"';
		stroke_color.Render(out);
		out << "stroke-width=\\" << '"' << stroke_width << "\\" << '"' << ' ';
		if (stroke_linecap.has_value()) {
			out << "stroke-linecap=\\" << '"' << stroke_linecap.value() << "\\" << '"' << ' ';
		}
		if (stroke_linejoin.has_value()) {
			out << "stroke-linejoin=\\" << '"' << stroke_linejoin.value() << "\\" << '"' << ' ';
		}
		out << ">" << text << "</text>";
	}
	void Document::Render(ostream& out) const {
		out << "<?xml version=\\" << '"' << "1.0\\" << '"' << "encoding=\\" << '"' << "UTF-8\\" << '"' << "?>";
		out << "<svg xmlns=\\" << '"' << "http://www.w3.org/2000/svg\\" << '"' << "version=\\" << '"' << "1.1\\" << '"' << ">";
		for (auto object : objects) {
			object->Render(out);
		}
		out << "</svg>";
	}
}