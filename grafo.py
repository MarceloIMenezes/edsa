from ctypes import c_size_t, c_void_p, cdll

libgrafo = cdll.LoadLibrary('./libgrafo.so')

grafo_new = libgrafo.grafo_new
grafo_new.restype = c_void_p
grafo_new.argtypes = [c_size_t]

numero_de_vertices = libgrafo.grafo_numero_de_vertices
numero_de_vertices.restype = c_size_t
numero_de_vertices.argtypes = [c_void_p]

class Grafo(object):
    def __init__(self, n_vertices):
        self.obj = grafo_new(n_vertices)

    def numero_de_vertices(self):
        return numero_de_vertices(self.obj)
