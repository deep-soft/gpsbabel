/*
    Read Yahoo Geocoded files.

    Copyright (C) 2002-2020 Robert Lipe, gpsbabel.org

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

 */
#ifndef YAHOO_H_INCLUDED_
#define YAHOO_H_INCLUDED_

#include <QtCore/QString>               // for QString
#include <QtCore/QStringList>           // for QStringList
#include <QtCore/QXmlStreamAttributes>

#include "defs.h"
#include "format.h"                     // for Format
#include "xmlgeneric.h"                     // for Format

class YahooFormat : public Format
{
public:
    YahooFormat() {printf("Ctor\n");}
  QVector<arglist_t>* get_args() override
  {
    printf("Getting args\n");

    return &yahoo_args;
  }

  ff_type get_type() const override
  {
    return ff_type_file;
  }

  QVector<ff_cap> get_cap() const override {
    printf("Getting Cap\n");
    return FF_CAP_RW_ALL;
    //return { (ff_cap) ff_cap_read };
  }

  QString get_encode() const override {
    return CET_CHARSET_ASCII;
  }

  int get_fixed_encode() const override {
    return 0;
  }

  void rd_init(const QString&) override;
  void read() override;
  void rd_deinit() override;

private:
    Waypoint* wpt_tmp;
    char* as;

    QVector<arglist_t> yahoo_args = {
      {
        "addrsep", &as,
        "String to separate concatenated address fields (default=\", \")",
        ", ", ARGTYPE_STRING, ARG_NOMINMAX, nullptr
      },
    };
    void wpt_s(const QString &, const QXmlStreamAttributes *);

 void wpt_e(const QString &, const QXmlStreamAttributes *);
 void wpt_lat(const QString &, const QXmlStreamAttributes *);
 void wpt_lon(const QString &, const QXmlStreamAttributes *);
 void wpt_addr(const QString &, const QXmlStreamAttributes *);
 xg_tag_mapping gl_map[];

#if 0
      static xg_tag_mapping gl_map[] = {
      { wpt_s,	cb_start, "/ResultSet/Result" },
      { wpt_lat,	cb_cdata, "/ResultSet/Result/Latitude" },
      { wpt_lon,	cb_cdata, "/ResultSet/Result/Longitude" },
      { wpt_addr,	cb_cdata, "/ResultSet/Result/Address" },
      { wpt_addr,	cb_cdata, "/ResultSet/Result/City" },
      { wpt_addr,	cb_cdata, "/ResultSet/Result/State" },
      { wpt_addr,	cb_cdata, "/ResultSet/Result/Zip" },
      { wpt_addr,	cb_cdata, "/ResultSet/Result/Country" },
      { wpt_e,	cb_end,   "/ResultSet/Result" },
      { nullptr,	(xg_cb_type)0,         nullptr}
      };
#endif


};

#endif //  YAHOO_H_INCLUDED_