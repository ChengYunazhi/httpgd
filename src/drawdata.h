//#include <iostream>
#include <string>
#include <vector>
//#include <algorithm>

namespace httpgd
{
  namespace dc
  {
    typedef enum
    {
      GC_ROUND_CAP = 1,
      GC_BUTT_CAP = 2,
      GC_SQUARE_CAP = 3
    } GC_lineend;

    typedef enum
    {
      GC_ROUND_JOIN = 1,
      GC_MITRE_JOIN = 2,
      GC_BEVEL_JOIN = 3
    } GC_linejoin;

    // struct GContext
    // {
    //     /*
    //      * Colours
    //      *
    //      * NOTE:  Alpha transparency included in col & fill
    //      */
    //     int col;             /* pen colour (lines, text, borders, ...) */
    //     int fill;            /* fill colour (for polygons, circles, rects, ...) */
    //     double gamma;        /* Gamma correction */
    //     /*
    //      * Line characteristics
    //      */
    //     double lwd;          /* Line width (roughly number of pixels) */
    //     int lty;             /* Line type (solid, dashed, dotted, ...) */
    //     GC_lineend lend;     /* Line end */
    //     GC_linejoin ljoin;   /* line join */
    //     double lmitre;       /* line mitre */
    //     /*
    //      * Text characteristics
    //      */
    //     double cex;          /* Character expansion (font size = fontsize*cex) */
    //     double ps;           /* Font size in points */
    //     double lineheight;   /* Line height (multiply by font size) */
    //     int fontface;        /* Font face (plain, italic, bold, ...) */
    //     char fontfamily[201]; /* Font family */
    // }

    class DrawCall
    {
    public:
      int m_col;
      int m_fill;
      double m_gamma;
      double m_lwd;
      int m_lty;
      GC_lineend m_lend;
      GC_linejoin m_ljoin;
      double m_lmitre;

      DrawCall(const std::string &name);
      virtual ~DrawCall();

      virtual void to_svg(std::string &buf);

    protected:
      std::string m_name;
    };

    class Text : public DrawCall
    {
    public:
      Text(double x, double y, const std::string &str, double rot, double hadj);
      void to_svg(std::string &buf);

      std::string m_font_family;
      double m_fontsize;
      bool m_bold;
      bool m_italic;
      double m_txtwidth_px;

    private:
      double m_x, m_y, m_rot, m_hadj;
      std::string m_str;
    };

    class Circle : public DrawCall
    {
    public:
      Circle(double x, double y, double r);
      void to_svg(std::string &buf);

    private:
      double m_x, m_y, m_r;
    };

    class Line : public DrawCall
    {
    public:
      Line(double x1, double y1, double x2, double y2);
      void to_svg(std::string &buf);

    private:
      double m_x1, m_y1, m_x2, m_y2;
    };

    class Rect : public DrawCall
    {
    public:
      Rect(double x0, double y0, double x1, double y1);
      void to_svg(std::string &buf);

    private:
      double m_x0, m_y0, m_x1, m_y1;
    };

    class Polyline : public DrawCall
    {
    public:
      Polyline(int n, std::vector<double> &x, std::vector<double> &y);
      void to_svg(std::string &buf);

    private:
      int m_n;
      std::vector<double> m_x;
      std::vector<double> m_y;
    };
    class Polygon : public DrawCall
    {
    public:
      Polygon(int n, std::vector<double> &x, std::vector<double> &y);
      void to_svg(std::string &buf);

    private:
      int m_n;
      std::vector<double> m_x;
      std::vector<double> m_y;
    };

    class Page
    {
    public:
      double m_width;
      double m_height;
      Page(double width, double height);
      ~Page();
      void put(DrawCall *dc);
      void clear();
      void to_svg(std::string &buf);
      int get_upid();

    private:
      std::vector<DrawCall *> m_dcs;
      int m_upid;
    };

  } // namespace dc
} // namespace httpgd