#include <iostream>
#include <pugixml.hpp>

#include <maolan/audio/clip.h>
#include <maolan/audio/connection.h>
#include <maolan/audio/ossin.h>
#include <maolan/audio/ossout.h>
#include <maolan/audio/track.h>
#include <maolan/io.h>
#include <maolan/utils.h>

namespace maolan
{
IO *xmlElement2IO(pugi::xml_node *n)
{
  audio::IO *io = nullptr;

  std::string name = n->name();
  if (name == "track")
  {
    io = new audio::Track(n->attribute("name").value());
    return io;
  }
  else if (name == "clip")
  {
    io = new audio::Clip(
        n->attribute("start").as_uint(), n->attribute("end").as_uint(),
        n->attribute("offset").as_uint(), n->attribute("path").value());
    for (auto parent = IO::begin(); parent != nullptr; parent = parent->next())
    {
      if (parent->name() == n->parent().parent().attribute("name").value())
      {
        io->parent(parent);
        break;
      }
    }
    return io;
  }
  else if (name == "input")
  {
    io = new audio::OSSIn(n->attribute("device").value(),
                          n->attribute("channels").as_int());
    return io;
  }
  else if (name == "output")
  {
    io = new audio::OSSOut(n->attribute("device").value(),
                           n->attribute("channels").as_int());
    return io;
  }
  else if (name == "connection")
  {
    maolan::audio::OSSOut *from = nullptr;
    maolan::audio::Track *to = nullptr;
    for (auto item = IO::begin(); item != nullptr; item = item->next())
    {
      if (item->type() == n->attribute("from").value())
      {
        from = (maolan::audio::OSSOut *)item;
      }
      if (item->name() == n->attribute("to").value())
      {
        to = dynamic_cast<maolan::audio::Track *>(item);
      }
    }
    from->connect(to);
  }
  return io;
}

pugi::xml_node loadXml(const char *path)
{
  pugi::xml_document doc;
  pugi::xml_parse_result result =
      doc.load_file(path, pugi::parse_default | pugi::parse_declaration);
  if (!result)
  {
    std::cerr << "Parse error: " << result.description();
    std::cerr << ", character pos= " << result.offset << std::endl;
  }
  pugi::xml_node root = doc.document_element();
  return root;
}

} // namespace maolan
