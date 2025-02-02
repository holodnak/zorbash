//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_gfx.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

static void gfx_init_font_pixelart_small(void)
{
  std::initializer_list< std::string > tiles = {
      //////////////////////////////////////////////////////////////////
      // sp     !       "       #       $       %       &       '
      //////////////////////////////////////////////////////////////////
      "1.0",
      "1.1",
      "1.2",
      "1.3",
      "1.4",
      "1.5",
      "1.6",
      "1.7",
      //////////////////////////////////////////////////////////////////
      //  (     )       *       +       ,       -       .       /
      //////////////////////////////////////////////////////////////////
      "1.8",
      "1.9",
      "1.10",
      "1.11",
      "1.12",
      "1.13",
      "1.14",
      "1.15",
      //////////////////////////////////////////////////////////////////
      //  0     1       2       3       4       5       6       7
      //////////////////////////////////////////////////////////////////
      "1.16",
      "1.17",
      "1.18",
      "1.19",
      "1.20",
      "1.21",
      "1.22",
      "1.23",
      //////////////////////////////////////////////////////////////////
      //  8     9       :       ;       <       =       >       ?
      //////////////////////////////////////////////////////////////////
      "1.24",
      "1.25",
      "1.26",
      "1.27",
      "1.28",
      "1.29",
      "1.30",
      "1.31",
      //////////////////////////////////////////////////////////////////
      //  @     A       B       C       D       E       F       G
      //////////////////////////////////////////////////////////////////
      "1.32",
      "1.33",
      "1.34",
      "1.35",
      "1.36",
      "1.37",
      "1.38",
      "1.39",
      //////////////////////////////////////////////////////////////////
      //  H     I       J       K       L       M       N       O
      //////////////////////////////////////////////////////////////////
      "1.40",
      "1.41",
      "1.42",
      "1.43",
      "1.44",
      "1.45",
      "1.46",
      "1.47",
      //////////////////////////////////////////////////////////////////
      //  P     Q       R       S       T       U       V       W
      //////////////////////////////////////////////////////////////////
      "1.48",
      "1.49",
      "1.50",
      "1.51",
      "1.52",
      "1.53",
      "1.54",
      "1.55",
      //////////////////////////////////////////////////////////////////
      //  X     Y       Z       [       \       ]       ^       _
      //////////////////////////////////////////////////////////////////
      "1.56",
      "1.57",
      "1.58",
      "1.59",
      "1.60",
      "1.61",
      "1.62",
      "1.63",
      //////////////////////////////////////////////////////////////////
      //  `     a       b       c       d       e       f       g
      //////////////////////////////////////////////////////////////////
      "1.64",
      "1.65",
      "1.66",
      "1.67",
      "1.68",
      "1.69",
      "1.70",
      "1.71",
      //////////////////////////////////////////////////////////////////
      //  h     i       j       k       l       m       n       o
      //////////////////////////////////////////////////////////////////
      "1.72",
      "1.73",
      "1.74",
      "1.75",
      "1.76",
      "1.77",
      "1.78",
      "1.79",
      //////////////////////////////////////////////////////////////////
      //  p     q       r       s       t       u       v       w
      //////////////////////////////////////////////////////////////////
      "1.80",
      "1.81",
      "1.82",
      "1.83",
      "1.84",
      "1.85",
      "1.86",
      "1.87",
      //////////////////////////////////////////////////////////////////
      //  x     y       z       {       |       }       ~       del
      //////////////////////////////////////////////////////////////////
      "1.88",
      "1.89",
      "1.90",
      "1.91",
      "1.92",
      "1.93",
      "1.94",
      "1.95",
      //////////////////////////////////////////////////////////////////
      //  blk  [$]     lbs    arrow
      //////////////////////////////////////////////////////////////////
      "1.96",
      "1.97",
      "1.98",
      "1.99",
      "1.100",
      "",
      "",
      "",
  };

  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/fonts/font-pixelart-small.tga", "font_pixelart_small", UI_FONT_SMALL_WIDTH,
                        UI_FONT_SMALL_HEIGHT, arr, GL_NEAREST);
}

static void gfx_init_font_pixelart_large(void)
{
  std::initializer_list< std::string > tiles = {
      //////////////////////////////////////////////////////////////////
      // sp     !       "       #       $       %       &       '
      //////////////////////////////////////////////////////////////////
      "2.0",
      "2.1",
      "2.2",
      "2.3",
      "2.4",
      "2.5",
      "2.6",
      "2.7",
      //////////////////////////////////////////////////////////////////
      //  (     )       *       +       ,       -       .       /
      //////////////////////////////////////////////////////////////////
      "2.8",
      "2.9",
      "2.10",
      "2.11",
      "2.12",
      "2.13",
      "2.14",
      "2.15",
      //////////////////////////////////////////////////////////////////
      //  0     1       2       3       4       5       6       7
      //////////////////////////////////////////////////////////////////
      "2.16",
      "2.17",
      "2.18",
      "2.19",
      "2.20",
      "2.21",
      "2.22",
      "2.23",
      //////////////////////////////////////////////////////////////////
      //  8     9       :       ;       <       =       >       ?
      //////////////////////////////////////////////////////////////////
      "2.24",
      "2.25",
      "2.26",
      "2.27",
      "2.28",
      "2.29",
      "2.30",
      "2.31",
      //////////////////////////////////////////////////////////////////
      //  @     A       B       C       D       E       F       G
      //////////////////////////////////////////////////////////////////
      "2.32",
      "2.33",
      "2.34",
      "2.35",
      "2.36",
      "2.37",
      "2.38",
      "2.39",
      //////////////////////////////////////////////////////////////////
      //  H     I       J       K       L       M       N       O
      //////////////////////////////////////////////////////////////////
      "2.40",
      "2.41",
      "2.42",
      "2.43",
      "2.44",
      "2.45",
      "2.46",
      "2.47",
      //////////////////////////////////////////////////////////////////
      //  P     Q       R       S       T       U       V       W
      //////////////////////////////////////////////////////////////////
      "2.48",
      "2.49",
      "2.50",
      "2.51",
      "2.52",
      "2.53",
      "2.54",
      "2.55",
      //////////////////////////////////////////////////////////////////
      //  X     Y       Z       [       \       ]       ^       _
      //////////////////////////////////////////////////////////////////
      "2.56",
      "2.57",
      "2.58",
      "2.59",
      "2.60",
      "2.61",
      "2.62",
      "2.63",
      //////////////////////////////////////////////////////////////////
      //  `     a       b       c       d       e       f       g
      //////////////////////////////////////////////////////////////////
      "2.64",
      "2.65",
      "2.66",
      "2.67",
      "2.68",
      "2.69",
      "2.70",
      "2.71",
      //////////////////////////////////////////////////////////////////
      //  h     i       j       k       l       m       n       o
      //////////////////////////////////////////////////////////////////
      "2.72",
      "2.73",
      "2.74",
      "2.75",
      "2.76",
      "2.77",
      "2.78",
      "2.79",
      //////////////////////////////////////////////////////////////////
      //  p     q       r       s       t       u       v       w
      //////////////////////////////////////////////////////////////////
      "2.80",
      "2.81",
      "2.82",
      "2.83",
      "2.84",
      "2.85",
      "2.86",
      "2.87",
      //////////////////////////////////////////////////////////////////
      //  x     y       z       {       |       }       ~       del
      //////////////////////////////////////////////////////////////////
      "2.88",
      "2.89",
      "2.90",
      "2.91",
      "2.92",
      "2.93",
      "2.94",
      "2.95",
      //////////////////////////////////////////////////////////////////
      //  blk  [$]     lbs    arrow
      //////////////////////////////////////////////////////////////////
      "2.96",
      "2.97",
      "2.98",
      "2.99",
      "2.100",
      "2.101",
      "2.102",
      "2.103",
      "2.104",
      "2.105",
      "2.106",
      "2.107",
      "2.108",
      "2.109",
      "2.110",
      "2.111",
      "2.112",
      "2.113",
      "2.114",
      "2.115",
      "2.116",
      "2.117",
      "2.118",
      "2.119",
      "2.120",
      "2.121",
      "2.122",
      "2.123",
      "2.124",
      "2.125",
      "2.126",
      "2.127",
      "2.128",
      "2.129",
      "2.130",
      "2.131",
      "2.132",
      "2.133",
      "2.134",
      "2.135",
      "2.136",
      "2.137",
      "2.138",
      "2.139",
      "2.140",
      "2.141",
      "2.142",
      "2.143",
      "2.144",
      "2.145",
      "2.146",
      "2.147",
      "2.148",
      "2.149",
      "2.150",
      "2.151",
      "2.152",
      "2.153",
      "2.154",
      "2.155",
      "2.156",
      "2.157",
      "2.158",
      "2.159",
      "2.160",
      "2.161",
      "2.162",
      "2.163",
      "2.164",
      "2.165",
      "2.166",
      "2.167",
      "2.168",
      "2.169",
      "2.170",
      "2.171",
      "2.172",
      "2.173",
      "2.174",
      "2.175",
      "2.176",
      "2.177",
      "2.178",
      "2.179",
      "2.180",
      "2.181",
      "2.182",
      "2.183",
      "2.184",
      "2.185",
      "2.186",
      "2.187",
      "2.188",
      "2.189",
      "2.190",
      "2.191",
      "2.192",
      "2.193",
      "2.194",
      "2.195",
      "2.196",
      "2.197",
      "2.198",
      "2.199",
      "2.200",
      "2.201",
      "2.202",
      "2.203",
      "2.204",
      "2.205",
      "2.206",
      "2.207",
      "2.208",
      "2.209",
      "2.210",
      "2.211",
      "2.212",
      "2.213",
      "2.214",
      "2.215",
      "2.216",
      "2.217",
      "2.218",
      "2.219",
      "2.220",
      "2.221",
      "2.222",
      "2.223",
  };

  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/fonts/font-pixelart-large.tga", "font_pixelart_large", UI_FONT_LARGE_WIDTH,
                        UI_FONT_LARGE_HEIGHT, arr, GL_NEAREST);
}

static void gfx_init_font_ascii(void)
{
  std::initializer_list< std::string > tiles = {
      //////////////////////////////////////////////////////////////////
      // sp     !       "       #       $       %       &       '
      //////////////////////////////////////////////////////////////////
      "3.0",
      "3.1",
      "3.2",
      "3.3",
      "3.4",
      "3.5",
      "3.6",
      "3.7",
      //////////////////////////////////////////////////////////////////
      //  (     )       *       +       ,       -       .       /
      //////////////////////////////////////////////////////////////////
      "3.8",
      "3.9",
      "3.10",
      "3.11",
      "3.12",
      "3.13",
      "3.14",
      "3.15",
      //////////////////////////////////////////////////////////////////
      //  0     1       2       3       4       5       6       7
      //////////////////////////////////////////////////////////////////
      "3.16",
      "3.17",
      "3.18",
      "3.19",
      "3.20",
      "3.21",
      "3.22",
      "3.23",
      //////////////////////////////////////////////////////////////////
      //  8     9       :       ;       <       =       >       ?
      //////////////////////////////////////////////////////////////////
      "3.24",
      "3.25",
      "3.26",
      "3.27",
      "3.28",
      "3.29",
      "3.30",
      "3.31",
      //////////////////////////////////////////////////////////////////
      //  @     A       B       C       D       E       F       G
      //////////////////////////////////////////////////////////////////
      "3.32",
      "3.33",
      "3.34",
      "3.35",
      "3.36",
      "3.37",
      "3.38",
      "3.39",
      //////////////////////////////////////////////////////////////////
      //  H     I       J       K       L       M       N       O
      //////////////////////////////////////////////////////////////////
      "3.40",
      "3.41",
      "3.42",
      "3.43",
      "3.44",
      "3.45",
      "3.46",
      "3.47",
      //////////////////////////////////////////////////////////////////
      //  P     Q       R       S       T       U       V       W
      //////////////////////////////////////////////////////////////////
      "3.48",
      "3.49",
      "3.50",
      "3.51",
      "3.52",
      "3.53",
      "3.54",
      "3.55",
      //////////////////////////////////////////////////////////////////
      //  X     Y       Z       [       \       ]       ^       _
      //////////////////////////////////////////////////////////////////
      "3.56",
      "3.57",
      "3.58",
      "3.59",
      "3.60",
      "3.61",
      "3.62",
      "3.63",
      //////////////////////////////////////////////////////////////////
      //  `     a       b       c       d       e       f       g
      //////////////////////////////////////////////////////////////////
      "3.64",
      "3.65",
      "3.66",
      "3.67",
      "3.68",
      "3.69",
      "3.70",
      "3.71",
      //////////////////////////////////////////////////////////////////
      //  h     i       j       k       l       m       n       o
      //////////////////////////////////////////////////////////////////
      "3.72",
      "3.73",
      "3.74",
      "3.75",
      "3.76",
      "3.77",
      "3.78",
      "3.79",
      //////////////////////////////////////////////////////////////////
      //  p     q       r       s       t       u       v       w
      //////////////////////////////////////////////////////////////////
      "3.80",
      "3.81",
      "3.82",
      "3.83",
      "3.84",
      "3.85",
      "3.86",
      "3.87",
      //////////////////////////////////////////////////////////////////
      //  x     y       z       {       |       }       ~       del
      //////////////////////////////////////////////////////////////////
      "3.88",
      "3.89",
      "3.90",
      "3.91",
      "3.92",
      "3.93",
      "3.94",
      "3.95",
      //////////////////////////////////////////////////////////////////
      "3.96",
      "3.97",
      "3.98",
      "3.99",
      "3.100",
      "3.101",
      "3.102",
      "3.103",
      "3.104",
      "3.105",
      "3.106",
      "3.107",
      "3.108",
      "3.109",
      "3.110",
      "3.111",
      //////////////////////////////////////////////////////////////////
      "3.112",
      "3.113",
      "3.114",
      "3.115",
      "3.116",
      "3.117",
      "3.118",
      "3.119",
      "3.120",
      "3.121",
      "3.122",
      "3.123",
      "3.124",
      "3.125",
      "3.126",
      "3.127",
      //////////////////////////////////////////////////////////////////
      "3.128",
      "3.129",
      "3.130",
      "3.131",
      "3.132",
      "3.133",
      "3.134",
      "3.135",
      "3.136",
      "3.137",
      "3.138",
      "3.139",
      "3.140",
      "3.141",
      "3.142",
      "3.143",
      //////////////////////////////////////////////////////////////////
      "3.144",
      "3.145",
      "3.146",
      "3.147",
      "3.148",
      "3.149",
      "3.150",
      "3.151",
      "3.152",
      "3.153",
      "3.154",
      "3.155",
      "3.156",
      "3.157",
      "3.158",
      "3.159",
      //////////////////////////////////////////////////////////////////
      "3.160",
      "3.161",
      "3.162",
      "3.163",
      "3.164",
      "3.165",
      "3.166",
      "3.167",
      "3.168",
      "3.169",
      "3.170",
      "3.171",
      "3.172",
      "3.173",
      "3.174",
      "3.175",
      //////////////////////////////////////////////////////////////////
      "3.176",
      "3.177",
      "3.178",
      "3.179",
      "3.180",
      "3.181",
      "3.182",
      "3.183",
      "3.184",
      "3.185",
      "3.186",
      "3.187",
      "3.188",
      "3.189",
      "3.190",
      "3.191",
      //////////////////////////////////////////////////////////////////
      "3.192",
      "3.193",
      "3.194",
      "3.195",
      "3.196",
      "3.197",
      "3.198",
      "3.199",
      "3.200",
      "3.201",
      "3.202",
      "3.203",
      "3.204",
      "3.205",
      "3.206",
      "3.207",
      //////////////////////////////////////////////////////////////////
      "3.208",
      "3.209",
      "3.210",
      "3.211",
      "3.212",
      "3.213",
      "3.214",
      "3.215",
      "3.216",
      "3.217",
      "3.218",
      "3.219",
      "3.220",
      "3.221",
      "3.222",
      "3.223",
  };

  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/fonts/font-ascii.tga", "font_ascii", UI_FONT_ASCII_WIDTH, UI_FONT_ASCII_HEIGHT, arr,
                        GL_LINEAR);
}

static void gfx_init_ui(void) {}

void gfx_init(void)
{
  gfx_init_font_pixelart_small();
  gfx_init_font_pixelart_large();
  gfx_init_font_ascii();
  gfx_init_ui();
  gfx_init0();
  gfx_init1();
  gfx_init2();
  gfx_init3();
  gfx_init4();
  gfx_init5();
  gfx_init6();
  gfx_init7();
  gfx_init8();
  gfx_init9();
  gfx_init10();
  gfx_init11();
  gfx_init12();
  gfx_init13();
  gfx_init14();
  gfx_init15();
  gfx_init16();
}

void gfx_fini(void) {}
