/*
	Onion HTTP server library
	Copyright (C) 2010-2013 David Moreno Montero

	This library is free software; you can redistribute it and/or
	modify it under the terms of, at your choice:
	
	a. the GNU Lesser General Public License as published by the 
	 Free Software Foundation; either version 3.0 of the License, 
	 or (at your option) any later version.
	
	b. the GNU General Public License as published by the 
	 Free Software Foundation; either version 2.0 of the License, 
	 or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License and the GNU General Public License along with this 
	library; if not see <http://www.gnu.org/licenses/>.
	*/

#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "dict.hpp"

#include <string>
#include <onion/request.h>

namespace Onion{
  
  class Request{
    onion_request *ptr;
  public:
    Request(onion_request *_ptr) : ptr(_ptr){}
    
    std::string operator[](const std::string &h){
      return headers()[h];
    }
    
    const Dict headers() const{
      return Dict(onion_request_get_header_dict(ptr));
    }
    const Dict post() const{
			const onion_dict *d=onion_request_get_post_dict(ptr);
			if (d)
				return Dict(d);
			else
				return Dict();
    }
    const Dict query() const{
      return Dict(onion_request_get_query_dict(ptr));
    }
    Dict session() const{
			onion_dict *d=onion_request_get_session_dict(ptr);
			if (d)
				return Dict(d);
			else
				return Dict();
    }
    const Dict files() const{
      const onion_dict *d=onion_request_get_file_dict(ptr);
      if (d)
        return Dict(d);
      else
        return Dict();
    }
    bool hasFiles() const{
      return (onion_request_get_file_dict(ptr)) ? true : false;
    }
    std::string path() const{
			return onion_request_get_path(ptr);
		}
		onion_request *c_handler(){
			return ptr;
		}
  };
}

#endif
