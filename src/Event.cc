/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Event.hh"

using namespace Entropy::Theia;
using namespace std;

Event::Event(const size_t &id)
	: Entropy::Event(id)
{}

Event::~Event() = default;
