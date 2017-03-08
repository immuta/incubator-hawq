class Libhdfs3 < Formula
    url "git@github.com:immuta/incubator-hawq.git", :using => :git 
    version "2.2.31"

    depends_on "boost"
    depends_on "protobuf"
    depends_on "ossp-uuid"
    depends_on "libxml2" 
    depends_on "homebrew/dupes/krb5"
    depends_on "gsasl"
    depends_on "cmake"

    def install
        cd "depends/libhdfs3/osx" do
            system "chmod +x ./build.sh"
            system "./build.sh build_google_test"
            system "./build.sh", "install_package", "#{prefix}"
        end
    end
end
