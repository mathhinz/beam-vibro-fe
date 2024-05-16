from conan import ConanFile
from conan.tools.cmake import CMakeToolchain


class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("catch2/3.5.3")
        self.requires("eigen/3.4.0")
        self.requires("spectra/1.0.1")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()