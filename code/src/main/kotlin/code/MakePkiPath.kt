package code

import java.io.BufferedInputStream
import java.io.FileInputStream
import java.io.FileOutputStream
import java.security.cert.Certificate
import java.security.cert.CertificateFactory
import java.util.*

fun main(args: Array<String>) {

    if (args.isEmpty()) {
        println("Usage:: java MakePkiPath <certfile>")
        System.exit(1)
    }

    val cf = CertificateFactory.getInstance("X.509")
    val certs = ArrayList<Certificate>()

    for (arg in args) {
        FileInputStream(arg).use { fis ->
            BufferedInputStream(fis).use { bis ->
                while (bis.available() > 0) {
                    certs.add(cf.generateCertificate(bis))
                }
            }
        }
    }

    // print each certificate in the path
    for (cert in cf.generateCertPath(certs).certificates) {
        println(cert.toString())
    }

    println("Creating PkiPath")
    FileOutputStream("certs.pki").use { fos ->
        fos.write(cf.generateCertPath(certs).getEncoded("PkiPath"))
    }
}
