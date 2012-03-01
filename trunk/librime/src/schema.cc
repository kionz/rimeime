// vim: set sts=2 sw=2 et:
// encoding: utf-8
//
// Copyleft 2011 RIME Developers
// License: GPLv3
//
// 2011-05-08 GONG Chen <chen.sst@gmail.com>
//
#include <boost/algorithm/string.hpp>
#include <rime/schema.h>

namespace rime {

Schema::Schema() : schema_id_(".default") {
  config_.reset(Config::Require("config")->Create("default"));
  if (!config_ || !config_->GetString("schema/name", &schema_name_))
    schema_name_ = schema_id_;
}

Schema::Schema(const std::string &schema_id) : schema_id_(schema_id) {
  if (boost::starts_with(schema_id_, L".")) {
    config_.reset(Config::Require("config")->Create(schema_id.substr(1)));
  }
  else {
    config_.reset(Config::Require("schema_config")->Create(schema_id));
  }
  if (!config_ || !config_->GetString("schema/name", &schema_name_))
    schema_name_ = schema_id_;
}

int Schema::page_size() const {
  int page_size = 5;  // default
  if (config_) {
    config_->GetInt("menu/page_size", &page_size);
  }
  return page_size;
}

const std::string Schema::alternative_select_keys() const {
  std::string select_keys;
  if (config_) {
    config_->GetString("menu/alternative_select_keys", &select_keys);
  }
  return select_keys;
}


}  // namespace rime
