//
//     Copyright 2011, Kay Hayen, mailto:kayhayen@gmx.de
//
//     Part of "Nuitka", an optimizing Python compiler that is compatible and
//     integrates with CPython, but also works on its own.
//
//     If you submit Kay Hayen patches to this software in either form, you
//     automatically grant him a copyright assignment to the code, or in the
//     alternative a BSD license to the code, should your jurisdiction prevent
//     this. Obviously it won't affect code that comes to him indirectly or
//     code you don't submit to him.
//
//     This is to reserve my ability to re-license the code at any time, e.g.
//     the PSF. With this version of Nuitka, using it for Closed Source will
//     not be allowed.
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, version 3 of the License.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//     Please leave the whole of this copyright notice intact.
//

#include "nuitka/prelude.hpp"

extern PyObject *_python_str_plain_inspect;
extern PyObject *_python_int_0;

static char *kwlist[] = { (char *)"object", NULL };

static PyObject *_inspect_isfunction_replacement( PyObject *self, PyObject *args, PyObject *kwds )
{
    PyObject *object;

    if ( !PyArg_ParseTupleAndKeywords( args, kwds, "O:isfunction", kwlist, &object, NULL ))
    {
        return NULL;
    }

    if ( Nuitka_Function_Check( object ) || PyFunction_Check( object ) )
    {
        return INCREASE_REFCOUNT( Py_True );
    }
    else
    {
        return INCREASE_REFCOUNT( Py_False );
    }
}

static PyObject *_inspect_ismethod_replacement( PyObject *self, PyObject *args, PyObject *kwds )
{
    PyObject *object;

    if ( !PyArg_ParseTupleAndKeywords( args, kwds, "O:ismethod", kwlist, &object, NULL ))
    {
        return NULL;
    }

    if ( Nuitka_Method_Check( object ) || PyMethod_Check( object ) )
    {
        return INCREASE_REFCOUNT( Py_True );
    }
    else
    {
        return INCREASE_REFCOUNT( Py_False );
    }
}

static PyObject *_inspect_isgenerator_replacement( PyObject *self, PyObject *args, PyObject *kwds )
{
    PyObject *object;

    if ( !PyArg_ParseTupleAndKeywords( args, kwds, "O:isgenerator", kwlist, &object, NULL ))
    {
        return NULL;
    }

    if ( Nuitka_Generator_Check( object ) || PyGen_Check( object ) )
    {
        return INCREASE_REFCOUNT( Py_True );
    }
    else
    {
        return INCREASE_REFCOUNT( Py_False );
    }
}

static PyMethodDef _method_def_inspect_isfunction_replacement
{
    "isfunction",
    (PyCFunction)_inspect_isfunction_replacement,
    METH_KEYWORDS,
    NULL
};

static PyMethodDef _method_def_inspect_ismethod_replacement
{
    "ismethod",
    (PyCFunction)_inspect_ismethod_replacement,
    METH_KEYWORDS,
    NULL
};

static PyMethodDef _method_def_inspect_isgenerator_replacement
{
    "isgenerator",
    (PyCFunction)_inspect_isgenerator_replacement,
    METH_KEYWORDS,
    NULL
};

void patchInspectModule( void )
{
    PyObject *module_inspect = IMPORT_MODULE( _python_str_plain_inspect, Py_None, Py_None, _python_tuple_empty, _python_int_0 );
    assertObject( module_inspect );

    PyObject *inspect_isfunction_replacement = PyCFunction_New( &_method_def_inspect_isfunction_replacement, NULL );
    assertObject( inspect_isfunction_replacement );

    PyObject_SetAttrString( module_inspect, "isfunction", inspect_isfunction_replacement );

    PyObject *inspect_ismethod_replacement = PyCFunction_New( &_method_def_inspect_ismethod_replacement, NULL );
    assertObject( inspect_ismethod_replacement );

    PyObject_SetAttrString( module_inspect, "ismethod", inspect_ismethod_replacement );

    PyObject *inspect_isgenerator_replacement = PyCFunction_New( &_method_def_inspect_isgenerator_replacement, NULL );
    assertObject( inspect_isgenerator_replacement );

    PyObject_SetAttrString( module_inspect, "isgenerator", inspect_isgenerator_replacement );

}
