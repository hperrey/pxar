# this file is used to generate the cython API interface to Python using xdress
# for documentation see http://xdress.org

package = 'pyPxarCore'     # top-level python package name
packagedir = 'pyPxarCore'  # location of the python package
sourcedir = 'api'      # location of C/C++ source

# List of C++ standard library container template types
# to instantiate and wrap with Cython. See the type
# system documentation for more details.  Note that
# vectors are wrapped as numpy arrays of the appropriate
# type.  If the type has no corresponding primitive C++
# type, then a new numpy dtype is created to handle it.
# For example, this allows the wrapping of vector< vector<int> >
# as an np.array(..., dtype=xd_vector_int).
stlcontainers = [
    ('vector', 'uint16'),
    ('vector', 'pixelConfig'),
    ('vector', 'rocConfig'),
    ('vector', 'tbmConfig'),
    ('vector', ('vector', 'pixel') ),
    ('vector', ('vector', 'pixelConfig') ),
    ('vector', ('vector', ('pair', 'str','uchar'))),
    ('vector', ('pair', 'uchar','uchar')),
    ('vector', ('pair', 'Uint16','uchar')),
    ('vector', ('pair', 'uchar',('vector','pixel'))),
    ('vector', ('pair', 'uchar',('pair','uchar', ('vector','pixel')))),
    ('vector', ('pair', 'str','uchar')),
    ('vector', ('pair', 'str','double'))
    ]

# name of the C++ standard library container module in
# the packagedir
#stlcontainers_module = 'stlcontainers'  # default value

# List of classes to wrap.  These may take one of the following
# forms:
#
#   (classname, base source filename)
#   (classname, base source filename, base package filename)
#   (classname, base source filename, None)
#
# In the first case, the base source filename will be used as
# the base package name as well. In the last case, a None value
# will register this class for the purpose of generating other
# APIs, but will not create the corresponding bindings.  Additionally,
# if the "xdress.autoall" plugin is enabled, you may also use an
# asterix (or star) to tell xdress to search the source file for
# all classes, functions, and/or variables:
#
#   ('*', base source filename)
#   ('*', base source filename, base package filename)
#   ('*', base source filename, None)
#
# This is useful for wrapping larger existing libraries.
classes = [
#    ('*', 'api'),
    ('api', 'api'),
    ('dut', 'api'),
    ('pixel', 'api'),
    ('pixelConfig', 'api'),
    ('rocConfig', 'api'),
    ('tbmConfig', 'api'),
    ]

functions = []

# List of functions to wrap
#functions = [
#    ('*', 'reprocess'),
#    ('fillUraniumEnrichmentDefaults', 'enrichment_parameters'),
#    ]
