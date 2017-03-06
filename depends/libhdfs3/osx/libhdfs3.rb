class libhdfs3 < Formula
    url "https://github.com/immuta/incubator-hawq/archive/XAttrAndPatch.tar.gz"
    sha256 "1e6bc90c007d6dd895d71f60926a5d751d20614aa9f415eeec34d08ccc3a9f9e"

    depends_on "cmake"

    def install
        cd "depends/libhdfs3/osx" do
            system "./build.sh", "install_package", "#{prefix}"
        done
    end
