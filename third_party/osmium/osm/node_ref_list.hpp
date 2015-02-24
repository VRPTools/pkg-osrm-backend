#ifndef OSMIUM_OSM_NODE_REF_LIST_HPP
#define OSMIUM_OSM_NODE_REF_LIST_HPP

/*

This file is part of Osmium (http://osmcode.org/libosmium).

Copyright 2013,2014 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <cassert>
#include <cstddef>
#include <iterator>

#include <osmium/memory/item.hpp>
#include <osmium/osm/item_type.hpp>
#include <osmium/osm/node_ref.hpp>

namespace osmium {

    /**
     * A vector of NodeRef objects. Usually this is not instatiated directly,
     * but one of its subclasses are used.
     */
    template <osmium::item_type TItemType>
    class NodeRefList : public osmium::memory::Item {

    public:

        static constexpr osmium::item_type itemtype = TItemType;

        NodeRefList() noexcept :
            osmium::memory::Item(sizeof(NodeRefList), TItemType) {
        }

        bool empty() const noexcept {
            return sizeof(NodeRefList) == byte_size();
        }

        size_t size() const noexcept {
            assert((osmium::memory::Item::byte_size() - sizeof(NodeRefList)) % sizeof(NodeRef) == 0);
            return (osmium::memory::Item::byte_size() - sizeof(NodeRefList)) / sizeof(NodeRef);
        }

        const NodeRef& operator[](size_t n) const {
            const NodeRef* node_ref = &*(cbegin());
            return node_ref[n];
        }

        const NodeRef& front() const {
            return operator[](0);
        }

        const NodeRef& back() const {
            return operator[](size()-1);
        }

        bool is_closed() const {
            return front().ref() == back().ref();
        }

        bool ends_have_same_id() const {
            return front().ref() == back().ref();
        }

        bool ends_have_same_location() const {
            return front().location() == back().location();
        }

        typedef NodeRef* iterator;
        typedef const NodeRef* const_iterator;
        typedef std::reverse_iterator<const NodeRef*> const_reverse_iterator;

        iterator begin() {
            return iterator(data() + sizeof(NodeRefList));
        }

        iterator end() {
            return iterator(data() + byte_size());
        }

        const_iterator cbegin() const {
            return const_iterator(data() + sizeof(NodeRefList));
        }

        const_iterator cend() const {
            return const_iterator(data() + byte_size());
        }

        const_iterator begin() const {
            return cbegin();
        }

        const_iterator end() const {
            return cend();
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(cend());
        }

        const_reverse_iterator crend() const {
            return const_reverse_iterator(cbegin());
        }

    }; // class NodeRefList

} // namespace osmium

#endif // OSMIUM_OSM_NODE_REF_LIST_HPP
