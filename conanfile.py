from conan import ConanFile


class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"
    default_options = {
        "catch2/*:with_main": True,
    }

    def layout(self):
        self.folders.generators = "conan"

    def build_requirements(self):
        self.test_requires("catch2/2.13.9")
