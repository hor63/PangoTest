/*
 ============================================================================
 Name        : PangoTest.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstdio>

#include <pango/pango.h>
#include <pango/pangoft2.h>
#include <pango/pangocairo.h>


using namespace std;

int main(void) {


	std::string s( "Übermut tut selten gut. High spirits rarely do well"
			"\nBlaBlaBla. الأرواح عالية نادرا ما تفعل بشكل جيد. 兴致很高兴. 興致很高興. วิญญาณสูงไม่ค่อยทำได้ดี"
			"\nDer Plüschelch rührt keinen Huf. Die efter effter efffter effer efffer effffer efier effier efffier Ligatur"
			"\n1234567890,;.:-_#'áàéèâ gqaaQ");

	//const char* font = "Noto Serif,Noto Naskh Arabic,Noto Serif Thai,Noto Serif CJK SC,Noto Serif CJK TC,Noto Serif CJK JP Regular 30";
	//const char* font = "Noto Sans,Noto Sans Arabic,Noto Sans Thai Looped,Noto Sans CJK SC,Noto Sans CJK TC,Noto Sans CJK JP Regular 30";
	//const char* font = "Noto Serif,Noto Naskh Arabic,Noto Serif Thai,Noto Serif CJK SC,Noto Serif CJK TC,Noto Serif CJK JP Bold 30";
	const char* font = "Noto Sans,Noto Sans Arabic,Noto Sans Thai Looped,Noto Sans CJK SC,Noto Sans CJK TC,Noto Sans CJK JP Bold 30";

	//const char* font = "sans-serif 40px";
	//const char* font = "Roboto 40px";
	//const char* font = "Droid 40px";

	s += '\n';
	s += font;
	const char* text = s.c_str();
	string sText = text;

	std::string fileName (font);
    fileName += ".png";
    std::replace(fileName.begin(),fileName.end(), ' ', '_');

	  cairo_t *cr;
	  cairo_status_t status;
	  cairo_surface_t *surface;

	  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
	                                        2400,500);
	  cr = cairo_create (surface);

	  cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	  cairo_paint (cr);

      cairo_save (cr);


	  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);


//	PangoFontMap *pFontmap = pango_ft2_font_map_new();
//	PangoContext *pContext = pango_font_map_create_context (pFontmap);
//	PangoLayout  *pLayout  = pango_layout_new(pContext);
	PangoLayout  *pLayout  = pango_cairo_create_layout (cr);
	PangoFontDescription* pFontDescr = pango_font_description_from_string(font);

	pango_layout_set_font_description(pLayout,pFontDescr);

	pango_layout_set_text(pLayout,text,-1);

    pango_cairo_show_layout (cr, pLayout);

    cairo_restore (cr);

    status = cairo_surface_write_to_png (surface,fileName.c_str());


	cout << "strlen(text) = " << strlen(text) << " Number of characters = " << pango_layout_get_character_count(pLayout) << endl;
	cout << "height = " << pango_layout_get_height(pLayout) << " width = " << pango_layout_get_width(pLayout) << endl;
	cout << "line count = " << pango_layout_get_line_count (pLayout) << endl;
	int width, height;
	pango_layout_get_pixel_size(pLayout,&width,&height);
	cout << "width = " << width << " height = " << height << endl;

	// Iterate through the runs of the layout
	PangoLayoutIter *pIter = pango_layout_get_iter (pLayout);

	do {

		PangoGlyphItem *pRun = pango_layout_iter_get_run_readonly(pIter);

		if (pRun) {
			PangoRectangle inkRect,logRect;

			cout << "Run found." << endl;

			PangoLayoutLine* pLine = pango_layout_iter_get_line_readonly(pIter);
			pango_layout_line_get_extents(pLine,&inkRect,&logRect);

			cout << "	Line info:"
					<< " Is paragraph start: " << pLine->is_paragraph_start
					<< " Resolved_dir = " << pLine->resolved_dir
					<< " Text start index = " << pLine->start_index
					<< " Text length = " << pLine->length
					<< endl;

			cout << "		InkRect x = " << inkRect.x/double(PANGO_SCALE)
					<< " y = " << inkRect.y/double(PANGO_SCALE)
					<< " width = " << inkRect.width/double(PANGO_SCALE)
					<< " height = " << inkRect.height/double(PANGO_SCALE)
					<< endl;

			cout << "		LogRect x = " << logRect.x/double(PANGO_SCALE)
					<< " y = " << logRect.y/double(PANGO_SCALE)
					<< " width = " << logRect.width/double(PANGO_SCALE)
					<< " height = " << logRect.height/double(PANGO_SCALE)
					<< endl;

			pFontDescr = pango_font_describe(pRun->item->analysis.font);

			FT_Face ftFace = pango_fc_font_lock_face((PangoFcFont*)(pRun->item->analysis.font));

			cout << "	Font family = " << pango_font_description_get_family(pFontDescr)  << endl;
			cout << "	Font size = " << pango_font_description_get_size(pFontDescr)  << endl;
			cout << "	Font descr = " << pango_font_description_to_string(pFontDescr)  << endl;
			cout << "	Baseline = " << pango_layout_iter_get_baseline(pIter) / double(PANGO_SCALE) << endl;
			cout << "	Freetype: ftFace->family_name = " << ftFace->family_name
					<< " ftFace->size = " << ftFace->size->metrics.x_ppem << "x" << ftFace->size->metrics.y_ppem
					<< endl;


			pango_layout_iter_get_run_extents(pIter,&inkRect,&logRect);
			cout << "	InkRect x = " << inkRect.x/double(PANGO_SCALE)
					<< " y = " << inkRect.y/double(PANGO_SCALE)
					<< " width = " << inkRect.width/double(PANGO_SCALE)
					<< " height = " << inkRect.height/double(PANGO_SCALE)
					<< endl;
			cout << "	LogRect x = " << logRect.x/double(PANGO_SCALE)
					<< " y = " << logRect.y/double(PANGO_SCALE)
					<< " width = " << logRect.width/double(PANGO_SCALE)
					<< " height = " << logRect.height/double(PANGO_SCALE)
					<< endl;


			PangoGlyphItemIter pClusterIter;
			char const *runText = pango_layout_get_text(pLayout);
		    gboolean clusterFound;

		    clusterFound = pango_glyph_item_iter_init_start(&pClusterIter,pRun,runText);
			while (clusterFound) {

				string clText = sText.substr(pClusterIter.start_index,(pClusterIter.end_index-pClusterIter.start_index));

				int xPos;
				pango_glyph_string_index_to_x (pClusterIter.glyph_item->glyphs,
				                               (char*)(runText + pRun->item->offset),
				                               pRun->item->length,
				                               &pRun->item->analysis,
											   pClusterIter.start_index - pRun->item->offset,
				                               FALSE,
				                               &xPos);


				cout << "		Cluster:"
						 << " start_glyph = " << pClusterIter.start_glyph
						 << " end_glyph = " << pClusterIter.end_glyph
						 << " start_index = " << pClusterIter.start_index
						 << " end_index = " << pClusterIter.end_index
						 << " start_char = " << pClusterIter.start_char
						 << " end_char = " << pClusterIter.end_char
						 << " X position = " << xPos / double(PANGO_SCALE)
						 << " Cluster text = \"" << clText << "\""
						 << endl;

				clusterFound = pango_glyph_item_iter_next_cluster(&pClusterIter);

			}


			for (int i = 0 ; i < pRun->glyphs->num_glyphs; i++) {
				cout << "		Glyph["<<i<<"] = " << hex << pRun->glyphs->glyphs[i].glyph << dec <<  endl;
				cout << "			Width = " << pRun->glyphs->glyphs[i].geometry.width/double(PANGO_SCALE)
						<< " X = " << pRun->glyphs->glyphs[i].geometry.x_offset/double(PANGO_SCALE)
						<< " Y = " << pRun->glyphs->glyphs[i].geometry.y_offset/double(PANGO_SCALE)
						<< endl;
				FT_Error ftErr = FT_Load_Glyph(ftFace,pRun->glyphs->glyphs[i].glyph,0);
				if (ftErr) {
					cerr << " FT_Load_Glyph returned " << ftErr << endl;
				}
				ftErr = FT_Render_Glyph(ftFace->glyph,FT_RENDER_MODE_NORMAL);
				if (ftErr) {
					cerr << " FT_Render_Glyph returned " << ftErr << endl;
				} else {
					cout << "		Bitmap Position = " << ftFace->glyph->bitmap_left<<","<<ftFace->glyph->bitmap_top << endl;
					cout << "		Bitmap: Size = " << ftFace->glyph->bitmap.width << "x" << ftFace->glyph->bitmap.rows
							<< ", Pitch = " << ftFace->glyph->bitmap.pitch
							<< ", Bitmap left x top = " << ftFace->glyph->bitmap_left << "x" << ftFace->glyph->bitmap_top
							<< ", Pixel mode = " ;
					switch (ftFace->glyph->bitmap.pixel_mode) {
					case FT_PIXEL_MODE_MONO:
						cout << "FT_PIXEL_MODE_MONO" << endl;
						break;
					case FT_PIXEL_MODE_GRAY:
						cout << "FT_PIXEL_MODE_GRAY"
							<< " Number grays = " << ftFace->glyph->bitmap.num_grays
							<< endl;
						break;

					case FT_PIXEL_MODE_GRAY2:
						cout << "FT_PIXEL_MODE_GRAY2" << endl;
						break;

					case FT_PIXEL_MODE_GRAY4:
						cout << "FT_PIXEL_MODE_GRAY4" << endl;
						break;

					case FT_PIXEL_MODE_LCD:
						cout << "FT_PIXEL_MODE_LCD" << endl;
						break;
					case FT_PIXEL_MODE_LCD_V:
						cout << "FT_PIXEL_MODE_LCD_V" << endl;
						break;

					case FT_PIXEL_MODE_BGRA:
						cout << "FT_PIXEL_MODE_BGRA" << endl;
						break;
					default :
						cout << "Unknown pixel mode" << ftFace->glyph->bitmap.pixel_mode<< endl;
						break;

					}



				}

				const unsigned char* bitmapP = ftFace->glyph->bitmap.buffer;
				printf ("\n");
				for (int k = 0; k < ftFace->glyph->bitmap.rows; k++) {

					for (int l = 0; l < ftFace->glyph->bitmap.width; l++) {

						if (bitmapP[l] == 0) {
							printf (". ",(int)bitmapP[l]);
						} else {
							printf ("%2X",(int)bitmapP[l]);
						}

					}
					printf ("\n");
					bitmapP += ftFace->glyph->bitmap.pitch;

				}
				printf ("\n");

			}

			pango_fc_font_unlock_face((PangoFcFont*)(pRun->item->analysis.font));


		} else {
			cout << "Run empty" << endl;
		}

	} while (pango_layout_iter_next_run(pIter));

	pango_layout_iter_free(pIter);


	cout << "Hello World" << endl; /* prints Hello World */
	return 0;
}
