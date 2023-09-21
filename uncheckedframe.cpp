
#include "uncheckedframe.h" 

void uncheckedframe::print( std::ostream& out ) const
{
   out << f;
   out << "(level = " << level << ",distance = " << dist << ")\n";
}


bool 
uncheckedframe::secondisbetter::operator( ) ( const uncheckedframe& u1, const uncheckedframe& u2 ) const
{
   if (u1.dist > u2.dist)
        return true;
    else if (u1.dist < u2.dist)
        return false;
    // If distances are the same, compare levels
    else if (u1.level > u2.level)
        return true;
    else
        return false;
}
